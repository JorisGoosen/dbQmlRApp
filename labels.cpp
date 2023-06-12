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
					_db->tableExtractColumnDefValue(stmt, 2, _labelDef).toString()
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

int Labels::id(const QString & label)
{
	return _labelMap[label]->id;
}

int Labels::addLabel(Label * label)
{
	_labels.push_back(label);

	_idLabelMap[label->id	] = label;
	_labelMap[	label->label] = label;

	return label->id;
}

int Labels::addLabel(const QString & label, int value)
{
	int id = _db->runStatementsId(
				 ("INSERT INTO " + _tableName +	" (" + _db->tableColumnQueryFrag({_valueDef, _labelDef}) + ") VALUES (" + _db->tableColumnQueryFrag({_valueDef, _labelDef}, false, true) + ");").toStdString(),
				[&](sqlite3_stmt * stmt)
				{
					_db->tableBindColumnDefParameter(stmt, 1,	_valueDef, value);
					_db->tableBindColumnDefParameter(stmt, 2,	_labelDef, label);
				});

	return addLabel(new Label(id, value, label));
}
