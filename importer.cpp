#include "importer.h"
#include <QFile>


Importer::Importer(QObject *parent)
	: QAbstractTableModel{parent}
{

}

int Importer::rowCount(const QModelIndex &) const
{
	return _columns.size() == 0 ? 0 : _columns[0]->values.size();
}

int Importer::columnCount(const QModelIndex &) const
{
	return _columns.size();
}

QVariant Importer::data(const QModelIndex & index, int role) const
{
	if(		index.row()		>= rowCount()
		||	index.column()	>= columnCount()
		||	index.row()		<  0
		||	index.column()	<  0)
		return QVariant();

	return _columns[index.row()]->values[index.column()];
}

QVariant Importer::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(orientation == Qt::Vertical)	return QString::number(section);
	else							return section < 0 || section >= columnCount() ? QVariant() : _columns[section]->nameCSV + "\n" + _columns[section]->nameDB;
}

void Importer::importCSV(QString csvFileName)
{
	QFile csvFile(csvFileName);
	csvFile.open(QFile::OpenModeFlag::ReadOnly);
}


bool Importer::importCSV(QTextStream & csvStream, QChar sepa)
{
	clearColumns();
	csvStream.reset();

	beginResetModel();
	QString header = csvStream.readLine();

	for(const QString & columnName : header.split(sepa))
		_columns.push_back(new ImportColumn(columnName));

	size_t row = 0;
	for(QStringList line = csvStream.readLine().split(sepa)	;
		!csvStream.atEnd()									;
		row++, line = csvStream.readLine().split(sepa)		)
		for(size_t col=0; col<_columns.size(); col++)
			_columns[col]->values[row].push_back(int(col) < line.size() ? line[col] : "");



	endResetModel();

	return true;
}




void Importer::clearColumns()
{
	beginResetModel();
	for(ImportColumn * col : _columns)
		delete col;

	_columns.clear();
	endResetModel();
}
