#include "importer.h"
#include <QDateTime>
#include <QFile>
#include <QUrl>
#include <iostream>
#include "schoolscannertable.h"
#include "labels.h"

Importer::Importer(SchoolScannerTable * table, Labels * labels)
	: QAbstractTableModel{table}, _table(table), _labels(labels), _metrics(_metricFont)
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

QVariant Importer::data(const QModelIndex & index, int) const
{
	if(		index.row()		>= rowCount()
		||	index.column()	>= columnCount()
		||	index.row()		<  0
		||	index.column()	<  0)
		return QVariant();

	ImportColumn * column = _columns[index.column()];

	/*if(column->cd->columnType() == ColumnType::DateTime)
		return QDateTime::fromSecsSinceEpoch(column->values[index.row()].toInt()).toString("yyyy.MM.dd hh:mm");
	else */if(column->cd->columnType() == ColumnType::Label)
	{
		int value = _labels->value(column->values[index.row()].toInt());
		return column->values[index.row()] + ": " + _labels->label(column->values[index.row()].toInt()) + (value != -1 ? " " + QString::number(value) : "");
	}
	else if(column->cd->columnType() == ColumnType::Labels)
	{
		QStringList labelsHuman;
		for(const QString & split : column->values[index.row()].split(' '))
			labelsHuman.append(_labels->label(split.toInt()));
		return column->values[index.row()] + ": " + labelsHuman.join(", ");
	}
	return column->values[index.row()];
}

QVariant Importer::headerData(int section, Qt::Orientation orientation, int) const
{
	if(orientation == Qt::Vertical)	return QString::number(section);
	else							return section < 0 || section >= columnCount() ? QVariant() : _columns[section]->nameCSV + "\n\ndb: " + _columns[section]->nameDB;
}

void Importer::collectDbColumns()
{
	for(ImportColumn * column : _columns)
	{
		column->cd		= _table->findDbColumn(column->nameCSV);
		if(column->cd)
			column->nameDB = column->cd->dbName();
	}
}

void Importer::processValues()
{
	for(ImportColumn * column : _columns)
		if(column->cd)
		{
			switch(column->cd->columnType())
			{
			case ColumnType::Label:
				for(QString & val : column->values)
				{
					int id = _labels->addLabel(column->nameDB, val);
					val = QString::number(id); //Replace label by id in importcolumn
				}
				break;

			case ColumnType::Labels:
				for(QString & val : column->values)
				{
					QStringList newVal;
					for(const QString & choice : val.split(", "))
						newVal.append(QString::number(_labels->addLabel(column->nameDB, choice)));

					val = newVal.join(" ");
				}
				break;

			case ColumnType::DateTime:
				//for(QString & val : column->values)
				//	val = QString::number(QDateTime::fromString(val, "dd/MM/yyyy hh:mm:ss").toSecsSinceEpoch());
				break;

			default:
				break;
			}
	}
}

void Importer::importCsv(const QString & csvFileName)
{
	QString toLocalFile = QUrl(csvFileName).toLocalFile();
	std::cerr << "local path: " << toLocalFile.toStdString() << std::endl;
	QFile csvFile(toLocalFile);

	if(!csvFile.exists())
		emit openingFileFailed(csvFileName, "File does not exist!");

	else if(!csvFile.open(QIODevice::ReadOnly))
		emit openingFileFailed(csvFileName, "Couldnt open file!");

	else
	{
		QTextStream	csvStream(&csvFile);
		importCsv(csvStream);
	}
}


bool Importer::importCsv(QTextStream & csvStream, QChar sepa)
{
	clearColumns();
	csvStream.reset();

	beginResetModel();
	QString header = csvStream.readLine();

	for(const QString & columnName : header.split(sepa))
		_columns.push_back(new ImportColumn(columnName));

	for(QStringList line = csvStream.readLine().split(sepa)	;
		!csvStream.atEnd()									;
		line = csvStream.readLine().split(sepa)				)
		for(size_t col=0; col<_columns.size(); col++)
			_columns[col]->values.push_back(int(col) < line.size() ? line[col] : "");

	collectDbColumns();
	processValues();

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

int Importer::columnWidthProvider(int col)
{
	QRect maxBounds(0,0, _maxWidthCol, std::numeric_limits<int>::max());

	QString header = headerData(col, Qt::Horizontal).toString();



	QRect bounds = _metrics.boundingRect(maxBounds, Qt::TextWordWrap, header);

	int largestVal = bounds.width();

	for(int row=0; row<rowCount(); row++)
		largestVal = std::max(largestVal, _metrics.boundingRect(maxBounds, Qt::TextWordWrap, data(index(row, col)).toString()).width());

	return std::min(largestVal, _maxWidthCol) + _cellMargin;
}

int Importer::rowHeightProvider(int row)
{
	QRect maxBounds(0,0, _maxWidthCol, std::numeric_limits<int>::max());

	QString header = headerData(row, Qt::Vertical).toString();

	QRect bounds = _metrics.boundingRect(maxBounds, Qt::TextWordWrap, header);

	int largestVal = bounds.height();

	for(int column=0; column<columnCount(); column++)
	{
		const QString & val = data(index(row, column)).toString();
		largestVal = std::max(largestVal, _metrics.boundingRect(maxBounds, Qt::TextWordWrap, val).height());
	}

	return largestVal + _cellMargin;
}

QFont Importer::metricFont() const
{
	return _metricFont;
}

void Importer::setMetricFont(const QFont & newMetricFont)
{
	if (_metricFont == newMetricFont)
		return;
	_metricFont = newMetricFont;
	emit metricFontChanged();

	_metrics = QFontMetrics(_metricFont);
}

int Importer::cellMargin() const
{
	return _cellMargin;
}

void Importer::setCellMargin(int newCellMargin)
{
	if (_cellMargin == newCellMargin)
		return;
	_cellMargin = newCellMargin;
	emit cellMarginChanged();
}
