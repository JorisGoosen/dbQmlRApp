#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <filesystem>
#include <sqlite3.h>
#include "columndefinition.h"

//#define SIR_LOG_A_LOT

class Database : public QObject
{
  Q_OBJECT
public:

	typedef std::function<void(sqlite3_stmt *stmt)>										bindParametersType;
	typedef std::function<bool(	bindParametersType **	bindParameters, size_t row)>	bindParametersFactoryType;
	typedef std::function<void(size_t row, sqlite3_stmt *stmt)>							processRowType;
	typedef std::function<void(size_t row, size_t repetition, sqlite3_stmt *stmt)>		processRowRepeatedType;

	explicit Database(QObject *parent = nullptr);
	explicit Database(const std::filesystem::path & file, QObject *parent = nullptr);
	~Database() { close(); }

	void			runQuery(		const std::string & query,		std::function<void(sqlite3_stmt *stmt)>		bindParameters,				std::function<void(size_t row, sqlite3_stmt *stmt)>		processRow);	///< Runs a single query and then goes through the resultrows while calling processRow for each.
	void			runStatements(	const std::string & statements);																																				///< Runs several sql statements without looking at the results.
	int				runStatementsId(const std::string & statements);																																				///< Runs several sql statements only looking for a single returned value from the results.
	void			runStatements(	const std::string & statements, std::function<void(sqlite3_stmt *stmt)>	bindParameters);																						///< Runs several sql statements without looking at the results. Arguments can be set by supplying bindParameters.
	int				runStatementsId(const std::string & statements, std::function<void(sqlite3_stmt *stmt)>	bindParameters);																						///< Runs (several) sql statements and only looks for a single value, this would usually be a id resulting from an insert
	void			runStatements(	const std::string & statements, std::function<void(sqlite3_stmt *stmt)>	bindParameters,	std::function<void(size_t row, sqlite3_stmt *stmt)>	processRow);						///< Runs several sql statements. Arguments can be set by supplying bindParameters and use processRow to read from the results.

	void			transactionWriteBegin();						///< runs BEGIN EXCLUSIVE and waits for sqlite to not be busy anymore if some other process is writing. Tracks whether nested and only does BEGIN+COMMIT at lowest depth
	void			transactionWriteEnd(bool rollback = false);     ///< runs COMMIT or ROLLBACK based on rollback and ends the transaction.  Tracks whether nested and only does BEGIN+COMMIT at lowest depth
	void			transactionReadBegin();							///< runs BEGIN DEFERRED and waits for sqlite to not be busy anymore if some other process is writing  Tracks whether nested and only does BEGIN+COMMIT at lowest depth
	void			transactionReadEnd();							///< runs COMMIT and ends the transaction. Tracks whether nested and only does BEGIN+COMMIT at lowest depth

	std::string		dbFile();

	bool			tableExists(	const QString & tableName);
	void			tableDrop(		const QString & tableName);
	void			tableCreate(	const QString & tableName, const ColumnDefinitions & cols);
	void			tableWriteRows(	const QString & tableName, const ColumnDefinitions & cols, const std::vector<QVariantList> & rows);
	QString			tableColumnQueryFrag(const ColumnDefinitions & cols, bool includeType=false, bool questionMarks=false);
	int				tableRowCount(	const QString & tableName);
	QVariant		tableValue(		const QString & tableName, const ColumnDefinition * col, size_t row);
	QVariantList	tableValues(	const QString & tableName, const ColumnDefinition * col);

	void			setDbFile(const std::filesystem::path & file);

	void			tableBindColumnDefParameter(sqlite3_stmt * stmt, size_t param, const ColumnDefinition * colDef, QVariant val);
	QVariant		tableExtractColumnDefValue(	sqlite3_stmt * stmt, size_t param, const ColumnDefinition * colDef);


private:

  void			_runStatements(				const std::string & statements,	bindParametersType			*	bindParameters = nullptr,	processRowType			* processRow = nullptr);	///< Runs several sql statements without looking at the results. Unless processRow is not NULL, then this is called for each row.
  void			_runStatementsRepeatedly(	const std::string & statements, bindParametersFactoryType		bindParameterFactory,		processRowRepeatedType	* processRow = nullptr);

  void			create();										///< Creates a new sqlite database in sessiondir and loads it
  void			load();											///< Loads a sqlite database from sessiondir (after loading a jaspfile)
  void			close();										///< Closes the loaded database and disconnects

  int	_transactionWriteDepth	= 0,
		_transactionReadDepth	= 0;

  sqlite3	*	_db = nullptr;

  static std::string _wrap_sqlite3_column_text(sqlite3_stmt * stmt, int iCol);

  std::filesystem::path _dbFile;
};

#endif // DATABASE_H
