#ifndef LABELS_H
#define LABELS_H

#include <QObject>
#include <columndefinition.h>

class Database;

struct Label
{
	int		id,
			value;
	QString label;

	Label(int id, int value, QString label)
	: id(id), value(value), label(label)
	{}
};

class Labels : public QObject
{
	Q_OBJECT
public:
	explicit Labels(Database * db, QObject *parent = nullptr);
	~Labels();

	void loadLabels();

	QString label(	int				id);
	int		value(	int				id);
	int		id(		const QString &	label);

public slots:
	int addLabel(const QString & label, int value);
	int addLabel(Label * label);

signals:

private:
	ColumnDefinition			*	_idDef		= nullptr,
								*	_valueDef	= nullptr,
								*	_labelDef	= nullptr,
								*	_columnDef	= nullptr;
	ColumnDefinitions				_columnDefs;
	Database					*	_db			= nullptr;
	const QString					_tableName	= "Labels";
	std::vector<Label*>				_labels;
	std::map<int, Label*>			_idLabelMap;
	std::map<QString, Label*>		_labelMap;
};

#endif // LABELS_H
