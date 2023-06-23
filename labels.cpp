#include "labels.h"
#include "database.h"

typedef ColumnDefinition	CD;

Labels::Labels(Database * db, QObject *parent)
:	QObject{parent},
	_idDef(		new CD("Id",		"id",			ColumnType::PrimaryKey	)),
	_valueDef(	new CD("Value",		"value",		ColumnType::NumInt		)),
	_labelDef(	new CD("Label",		"label",		ColumnType::Text		)),
	_columnDef(	new CD("Column",	"column",		ColumnType::Text		)),
	_columnDefs({_idDef, _columnDef, _valueDef, _labelDef}),
	_db(db)
{
	loadLabels();
}

Labels::~Labels()
{
	delete _idDef;
	delete _valueDef;
	delete _labelDef;

	for(Label * label : _labels)
		delete label;
}

void Labels::loadLabels()
{
	if(!_db->tableExists(_tableName))
		_db->tableCreate(_tableName, _columnDefs);
	else
	{
		_db->runStatements(
					("SELECT " + _db->tableColumnQueryFrag(_columnDefs) + " FROM " + _tableName + ";").toStdString(),
					[](sqlite3_stmt *){},
					[&](size_t, sqlite3_stmt *stmt)
		{
			addLabel(
				new Label(
					_db->tableExtractColumnDefValue(stmt, 0, _idDef).toInt(),
					_db->tableExtractColumnDefValue(stmt, 1, _valueDef).toInt(),
					_db->tableExtractColumnDefValue(stmt, 2, _labelDef).toString(),
					_db->tableExtractColumnDefValue(stmt, 3, _columnDef).toString()

			));
		}
		);

	}
}

QString Labels::label(int id)
{
	return _idLabelMap[id]->label;
}

int Labels::value(int id)
{
	return _idLabelMap[id]->value;
}

int Labels::id(const QString & label, const QString & column)
{
	return _labelMap[column][label]->id;
}

int Labels::addLabel(Label * label)
{
	_labels.push_back(label);

	_idLabelMap	[label->id]						= label;
	_labelMap	[label->column][label->label]	= label;

	return label->id;
}

int Labels::addLabel(const QString & column, const QString & label, int value)
{
	int id = -1;

	id = _db->runStatementsId(("SELECT " + _db->tableColumnQueryFrag({_idDef}) + " FROM " + _tableName + " WHERE " +  _db->tableColumnQueryFrag({_columnDef}) + " = ? AND " +  _db->tableColumnQueryFrag({_labelDef}) + " = ?;").toStdString(),
				[&](sqlite3_stmt * stmt)
				{
					_db->tableBindColumnDefParameter(stmt, 1,	_columnDef, column);
					_db->tableBindColumnDefParameter(stmt, 2,	_labelDef,	label);
				});

	if(id != -1)
		return id;

	if(value == -1)
	{
		static std::map<QString, int> defaultValues =
		{
			{ "Nooit",		1},
			{ "Soms",		2},
			{ "Vaak",		3},
			{ "Altijd",		4},

			{ "Af & toe",	2},
			{ "Maandelijks",3},
			{ "Wekelijks",	4},
			{ "Dagelijks",	5},

		};

		if(defaultValues.contains(label))
			value = defaultValues[label];
	}

	id = _db->runStatementsId(
				 ("INSERT INTO " + _tableName +	" (" + _db->tableColumnQueryFrag({_valueDef, _labelDef, _columnDef}) + ") VALUES (" + _db->tableColumnQueryFrag({_valueDef, _labelDef, _columnDef}, false, true) + ") RETURNING id;").toStdString(),
				[&](sqlite3_stmt * stmt)
				{
					_db->tableBindColumnDefParameter(stmt, 1,	_valueDef,	value);
					_db->tableBindColumnDefParameter(stmt, 2,	_labelDef,	label);
					_db->tableBindColumnDefParameter(stmt, 3,	_columnDef, column);
				});

	return addLabel(new Label(id, value, label, column));
}
