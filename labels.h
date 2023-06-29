#ifndef LABELS_H
#define LABELS_H

#include <QObject>
#include <columndefinition.h>

class Database;

struct Label
{
	int		id,
			value;
	QString label,
			column;

	Label(int id, int value, QString label, QString column="")
	: id(id), value(value), label(label), column(column)
	{}
};

typedef std::map<QString, std::map<QString, Label*>> columnLabelMap;

class Labels : public QObject
{
	Q_OBJECT
public:
	explicit Labels(Database * db, QObject *parent = nullptr);
	~Labels();

	static Labels * singleton() { return _singleton; }

	void loadLabels();

	QString label(	int				id);
	int		value(	int				id);
	int		id(		const QString &	label/*, const QString & column*/);

public slots:
	int addLabel(/*const QString & column,*/ const QString & label, int value=-1);
	int addLabel(Label * label);

signals:

private:
	static	Labels				*	_singleton;
	ColumnDefinition			*	_idDef		= nullptr,
								*	_valueDef	= nullptr,
								*	_labelDef	= nullptr/*,
								*	_columnDef	= nullptr*/;
	ColumnDefinitions				_columnDefs;
	Database					*	_db			= nullptr;
	const QString					_tableName	= "Labels";
	std::vector<Label*>				_labels;
	std::map<int, Label*>			_idLabelMap;
	std::map<QString, Label*>		_labelMap;
};

#endif // LABELS_H
