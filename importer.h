#ifndef IMPORTER_H
#define IMPORTER_H

#include <QAbstractTableModel>

struct ImportColumn
{
	ImportColumn(const QString & nameCSV, const QString & nameDB = "")
		: nameCSV(nameCSV), nameDB(nameDB == "" ? nameCSV : nameDB)
	{}

	QString					nameCSV,
							nameDB;
	std::vector<QString>	values;
};

typedef std::vector<ImportColumn*> ImportColumns;

class Importer : public QAbstractTableModel
{
public:
	explicit Importer(QObject *parent = nullptr);

	int			rowCount(	const QModelIndex &	parent = QModelIndex()) const override;
	int			columnCount(const QModelIndex &	parent = QModelIndex()) const override;
	QVariant	data(		const QModelIndex & index,										int role = Qt::DisplayRole) const override;
	QVariant	headerData(	int					section,	Qt::Orientation orientation,	int role = Qt::DisplayRole) const override;

	void		importCSV(QString csvFile);
	bool		importCSV(QTextStream & csvStream, QChar sepa = ',');
	void		clearColumns();

private:
	ImportColumns	_columns;

};

#endif // IMPORTER_H
