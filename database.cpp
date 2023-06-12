#include "database.h"
#include <iostream>

Database::Database(const std::filesystem::path & file, QObject *parent)
	: QObject{parent}
{
  setDbFile(file);
}

Database::Database(QObject *parent)
	: QObject{parent}
{
}

void Database::setDbFile(const std::filesystem::path & file)
{
	assert(_dbFile == "");
	_dbFile = file;

	if(!std::filesystem::exists(dbFile()))
		create();
	 else
		load();
}


void Database::create()
{
  assert(!_db);

  std::cout << "Creating database at '" << dbFile() << "'" << std::endl;

  if(std::filesystem::exists(dbFile()))
    {
      std::cout << "Database::create: Removing existing sqlite internal db at " << dbFile() << std::endl;
      std::filesystem::remove(dbFile());
    }

  int ret = sqlite3_open_v2(dbFile().c_str(), &_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, NULL);

  if(ret != SQLITE_OK)
  {
    std::cerr << "Couldnt open sqlite internal db, because of: " << (_db ? sqlite3_errmsg(_db) : "not even a broken sqlite3 obj was returned..." ) << std::endl;
    throw std::runtime_error("Couldnt create database....");
  }
  else
    std::cout << "Opened internal sqlite database for creation at '" << dbFile() << "'." << std::endl;
}

void Database::load()
{
  assert(!_db);

  std::cout << "Loading database from '" << dbFile() << "'" << std::endl;

  if(!std::filesystem::exists(dbFile()))
    throw std::runtime_error("Trying to load '" + dbFile() + "' but it doesn't exist!");

  int ret = sqlite3_open_v2(dbFile().c_str(), &_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_FULLMUTEX, NULL);

  if(ret != SQLITE_OK)
    {
      std::cout << "Couldnt open sqlite internal db, because of: " << (_db ? sqlite3_errmsg(_db) : "not even a broken sqlite3 obj was returned..." ) << std::endl;
      throw std::runtime_error("Couldnt open database....");
    }
  else
    std::cout << "Opened internal sqlite database for loading at '" << dbFile() << "'." << std::endl;
}

void Database::close()
{

  if(_db)
    {
      sqlite3_close(_db);
      _db = nullptr;
    }
}

void Database::runQuery(const std::string & query, std::function<void(sqlite3_stmt *stmt)> bindParameters, std::function<void(size_t row, sqlite3_stmt *stmt)> processRow)
{

  runStatements(query, bindParameters, processRow);
}

void Database::runStatements(	const std::string & statements)
{

  _runStatements(statements);
}

void Database::runStatements(	const std::string & statements, std::function<void(sqlite3_stmt *stmt)>	bindParameters)
{

  _runStatements(statements, &bindParameters);
}

int Database::runStatementsId(	const std::string & statements, std::function<void(sqlite3_stmt *stmt)>	bindParameters)
{

  int id = -1;
  std::function<void(size_t row, sqlite3_stmt *stmt)> processId = [&](size_t row, sqlite3_stmt *stmt)
  {
    int colCount = sqlite3_column_count(stmt);

    if(colCount)
      id = sqlite3_column_int(stmt, 0);

  };

  _runStatements(statements, &bindParameters, &processId);

#ifdef SIR_LOG_A_LOT
  std::cout << "Output for '" << statements << "' returns id:" << id << std::endl;
#endif
  return id;
}

int Database::runStatementsId(const std::string & statements)
{
  return runStatementsId(statements, [](sqlite3_stmt *stmt){});
}

void Database::runStatements(	const std::string & statements, std::function<void(sqlite3_stmt *stmt)>	bindParameters,	std::function<void(size_t row, sqlite3_stmt *stmt)>	processRow)
{

  _runStatements(statements, &bindParameters, &processRow);
}

void Database::_runStatements(const std::string & statements, bindParametersType * bindParameters, std::function<void(size_t row, sqlite3_stmt *stmt)> * processRow)
{
#ifdef SIR_LOG_A_LOT
	std::cout << "Running statements: '" << statements << "'" << std::endl;
#endif

	sqlite3_stmt * dbStmt = nullptr;

	const char	*	start	= statements.c_str(),
				*	current	= start,
				*	tail;
	size_t			total	= statements.size(),
					remain,
					row;
	int				ret		= SQLITE_OK;

	do
	{
		ret	= sqlite3_prepare_v2(_db, current, total - (current - start), &dbStmt, &tail);
		row = 0;

		if(bindParameters)
			(*bindParameters)(dbStmt);

		if(ret == SQLITE_OK && dbStmt)
		{
			do
			{
				ret = sqlite3_step(dbStmt);

				switch(ret)
				{
				case SQLITE_ERROR:
					{
						std::string errorMsg = "Running ```\n"+statements.substr(current - start)+"\n``` failed because of: `" + sqlite3_errmsg(_db);
						std::cout << errorMsg << std::endl;
						throw std::runtime_error(errorMsg);
					}

				case SQLITE_ROW:
					if(processRow)
						(*processRow)(row, dbStmt);

					break;
				}

				row++;
			}
			while((ret == SQLITE_BUSY || ret == SQLITE_ROW) && ret != SQLITE_DONE);

			ret = sqlite3_finalize(dbStmt);
			dbStmt = nullptr;
		}

		remain	= total - (tail - start);
		//std::cout << "Just ran `" + std::string(current, tail) + "` which returned " << ret << " and " << remain << " remaining." << std::endl;
		current	= tail;
	}
	while(remain > 1 && (ret == SQLITE_OK && ret != SQLITE_DONE));

	if(ret == SQLITE_ERROR)
	{
		std::string errorMsg = "Running ```\n"+statements+"\n``` failed because of: `" + sqlite3_errmsg(_db);
		std::cerr << errorMsg << std::endl;

		throw std::runtime_error(errorMsg);
	}

	if(ret == SQLITE_READONLY)
	{
		std::string errorMsg = "Running ```\n"+statements+"\n``` failed because the database is readonly...";
		std::cerr << errorMsg << std::endl;
		throw std::runtime_error(errorMsg);
	}
}

void Database::_runStatementsRepeatedly(const std::string & statements, std::function<bool(bindParametersType ** bindParameters, size_t row)> bindParameterFactory, std::function<void(size_t row, size_t repetition, sqlite3_stmt *stmt)> * processRow)
{

#ifdef SIR_LOG_A_LOT
  std::cout << "Running statements repeatedly: '" << statements << "'" << std::endl;
#endif

  sqlite3_stmt * dbStmt = nullptr;

  const char	*	start		= statements.c_str(),
      *	current		= start,
      *	tail;
  size_t			total		= statements.size(),
      remain,
      row			= 0,
      repetition	=  0;
  int				ret			= SQLITE_OK;

  std::function<void(sqlite3_stmt *stmt)> * bindParameters = nullptr;

  do
    {
      ret	= sqlite3_prepare_v2(_db, current, total - (current - start), &dbStmt, &tail);

      row = 0;

      while((ret == SQLITE_OK || ret == SQLITE_DONE) && dbStmt && bindParameterFactory(&bindParameters, row))
	{
	  if(bindParameters)
	    (*bindParameters)(dbStmt);

	  if((ret == SQLITE_OK || ret == SQLITE_DONE) && dbStmt)
	    {
	      do
		{
		  ret = sqlite3_step(dbStmt);

		  switch(ret)
		    {
		    case SQLITE_ERROR:
		      {
			std::string errorMsg = "Running `\n"+statements.substr(current - start)+"\n` repeatedly failed because of: `" + sqlite3_errmsg(_db);
			std::cerr << errorMsg << std::endl;
			throw std::runtime_error(errorMsg);
		      }

		    case SQLITE_ROW:
		      if(processRow)
			(*processRow)(row, repetition, dbStmt);

		      break;
		    }

		  row++;
		}
	      while((ret == SQLITE_BUSY || ret == SQLITE_ROW) && ret != SQLITE_DONE);
	    }

	  sqlite3_reset(dbStmt);
	  repetition++;
	}

      if(ret == SQLITE_ERROR)
	{
	  std::string errorMsg = "A problem occured trying to prepare statement `" + statements + "` and the error was: : `" + sqlite3_errmsg(_db);
	  std::cerr << errorMsg << std::endl;
	  throw std::runtime_error(errorMsg);
	}

      ret = sqlite3_finalize(dbStmt);
      dbStmt = nullptr;


      remain	= total - (tail - start);
      //std::cout << "Just ran `" + std::string(current, tail) + "` which returned " << ret << " and " << remain << " remaining." << std::endl;
      current	= tail;
    }
  while(remain > 1 && (ret == SQLITE_OK && ret != SQLITE_DONE));

  if(ret == SQLITE_ERROR)
    {
      std::string errorMsg = "Running ```\n"+statements+"\n``` failed because of: `" + sqlite3_errmsg(_db);
      std::cerr << errorMsg << std::endl;

      throw std::runtime_error(errorMsg);
    }

  if(ret == SQLITE_READONLY)
    {
      std::string errorMsg = "Running ```\n"+statements+"\n``` failed because the database is readonly...";
      std::cerr << errorMsg << std::endl;
      throw std::runtime_error(errorMsg);
    }
}

void Database::transactionWriteBegin()
{

  assert(_transactionReadDepth == 0);

  if(_transactionWriteDepth++ == 0)
    runStatements("BEGIN EXCLUSIVE"); //runStatements already has a while loop handling SQLITE_BUSY so this should work?
}

void Database::transactionReadBegin()
{

  assert(_transactionWriteDepth == 0);

  if(_transactionReadDepth++ == 0)
    runStatements("BEGIN DEFERRED");
}

void Database::transactionWriteEnd(bool rollback)
{

  assert(_transactionWriteDepth > 0);

  if(rollback)
    {
      runStatements("ROLLBACK");
      _transactionWriteDepth = 0;
      throw std::runtime_error("Rollback!"); //Might be better to use a subclass of std::runtime_error but for now this isnt even used anyway.
    }
  else if(--_transactionWriteDepth == 0)
    runStatements("COMMIT");
}

void Database::transactionReadEnd()
{

  assert(_transactionReadDepth > 0);

  if(--_transactionReadDepth == 0)
    runStatements("COMMIT");
}

std::string Database::dbFile()
{
	return _dbFile.generic_string();
}

bool Database::tableExists(const QString & tableName)
{
	return runStatementsId("SELECT count(name) FROM sqlite_master WHERE type='table' AND name='" + tableName.toStdString() + "';");
}

void Database::tableDrop(const QString & tableName)
{
	return runStatements("DROP TABLE " + tableName.toStdString() + ";");
}

void Database::tableCreate(const QString & tableName, const ColumnDefinitions & cols)
{
	QString optionalIdFrag = "id INTEGER PRIMARY KEY ASC,";

	for(ColumnDefinition * cd : cols)
		if(cd->columnType() == ColumnType::PrimaryKey)
		{
			optionalIdFrag = "";
			break;
		}

	QString query = "CREATE TABLE " + tableName + " (" + optionalIdFrag + " " + tableColumnQueryFrag(cols, true) + ");";

	runStatements(query.toStdString());
}



void Database::tableWriteRows(const QString & tableName, const ColumnDefinitions & cols, const std::vector<QVariantList> & rows)
{
	transactionWriteBegin();

	QString query = "INSERT INTO " + tableName + " ( " + tableColumnQueryFrag(cols) + ") VALUES ( " + tableColumnQueryFrag(cols, false, true) + ");";

	size_t rowOutside=0;
	bindParametersType _bindParams = [&](sqlite3_stmt * stmt)
	{
		for(size_t col=0; col<cols.size(); col++)
			tableBindColumnDefParameter(stmt, col+1, cols[col], rows[rowOutside][col]);
	};

	_runStatementsRepeatedly(query.toStdString(),
		[&](bindParametersType ** bindParams, size_t row)
		{
			rowOutside = row;
			(*bindParams) = &_bindParams;

			return rowOutside < rows.size();
		});


	transactionWriteEnd();

}

QString Database::tableColumnQueryFrag(const ColumnDefinitions & cols, bool includeType, bool questionMarks)
{
	QStringList list;

	for(const ColumnDefinition * col : cols)
		if(questionMarks)			list.append("?");
		else if(!includeType)		list.append(col->dbName());
		else						list.append(col->dbName() + " " + col->dbColType());

	return list.join(", ");
}

int Database::tableRowCount(const QString & tableName)
{
	return runStatementsId(("SELECT COUNT(*) FROM " + tableName).toStdString());
}

QVariant Database::tableValue(const QString & tableName, const ColumnDefinition * col, size_t row)
{
	const std::string	query	= ("SELECT " + col->dbName() + " FROM " + tableName + " WHERE id=?;").toStdString();

	int id = row + 1;

	bindParametersType bindParams = [&](sqlite3_stmt *stmt)
	{
		sqlite3_bind_int(	stmt, 1, id);
	};

	QVariant returnMe;

	processRowType processRow = [&](size_t, sqlite3_stmt *stmt)
	{
		returnMe = tableExtractColumnDefValue(stmt, 0, col);
	};

	runStatements(query, bindParams, processRow);

#ifdef SIR_LOG_A_LOT
	std::cout << query << " for id " << id << " returned " << returnMe.toString().toStdString() << std::endl;
#endif

	return returnMe;

}

void Database::tableBindColumnDefParameter(sqlite3_stmt * stmt, size_t param, const ColumnDefinition * colDef, QVariant val)
{
	switch(colDef->columnType())
	{
	case ColumnType::PrimaryKey:
	case ColumnType::NumInt:
	case ColumnType::DateTime: //unix epoch
		sqlite3_bind_int(stmt, param, val.toInt());
		return;

	case ColumnType::NumBool:
		if(val.typeId() == QMetaType::QString)
		{
			std::string str = val.toString().toStdString();
			sqlite3_bind_text(stmt, param, str.c_str(), str.size(), SQLITE_TRANSIENT);
			return;
		}

		sqlite3_bind_int(stmt, param, val.toInt());
		return;


	case ColumnType::Duration:
	case ColumnType::NumDbl:
		sqlite3_bind_double(stmt, param, val.toDouble());
		return;

	case ColumnType::Label:
		if(val.typeId() == QMetaType::Int)
		{
			sqlite3_bind_int(stmt, param, val.toInt());
			return;
		}
		[[fallthrough]];

	case ColumnType::Text:
		{
			std::string str = val.toString().toStdString();
			sqlite3_bind_text(stmt, param, str.c_str(), str.size(), SQLITE_TRANSIENT);
			return;
		}
	}
}

QVariant Database::tableExtractColumnDefValue(sqlite3_stmt * stmt, size_t param, const ColumnDefinition * colDef)
{
	switch(colDef->columnType())
	{
	case ColumnType::PrimaryKey:
	case ColumnType::NumInt:
	case ColumnType::NumBool:
	case ColumnType::DateTime: //unix epoch
		return QVariant(sqlite3_column_int(stmt, param));

	case ColumnType::Duration:
	case ColumnType::NumDbl:
		return QVariant(sqlite3_column_double(stmt, param));

	case ColumnType::Text:
		return QVariant(QString::fromStdString(_wrap_sqlite3_column_text(stmt, param)));

	case ColumnType::Label:
		if(sqlite3_column_type(stmt, param) == SQLITE_INTEGER)
			return QVariant(sqlite3_column_int(stmt, param));
		else
			return QVariant(QString::fromStdString(_wrap_sqlite3_column_text(stmt, param)));
	}
}

std::string Database::_wrap_sqlite3_column_text(sqlite3_stmt * stmt, int iCol)
{

  const unsigned char * col = sqlite3_column_text(stmt,	iCol);

  return !col ? "" : std::string(reinterpret_cast<const char*>(col));
}
