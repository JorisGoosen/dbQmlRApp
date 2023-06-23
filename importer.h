#ifndef IMPORTER_H
#define IMPORTER_H

#include <QAbstractTableModel>
#include <QFont>
#include <QFontMetrics>
#include "columndefinition.h"

class SchoolScannerTable;
class Labels;

struct ImportColumn
{
	ImportColumn(const QString & nameCSV, const QString & nameDB = "")
		: nameCSV(nameCSV), nameDB(nameDB == "" ? nameCSV : nameDB)
	{}

	QString						nameCSV,
								nameDB;
	std::vector<QString>		values;
	const ColumnDefinition	*	cd = nullptr;
};

typedef std::vector<ImportColumn*> ImportColumns;

class Importer : public QAbstractTableModel
{
	Q_OBJECT

	Q_PROPERTY(QFont	metricFont			READ metricFont			WRITE setMetricFont			NOTIFY metricFontChanged		)
	Q_PROPERTY(int		cellMargin			READ cellMargin			WRITE setCellMargin			NOTIFY cellMarginChanged		)

public:
	explicit Importer(SchoolScannerTable * table, Labels * labels);

	int			rowCount(	const QModelIndex &	parent = QModelIndex()) const override;
	int			columnCount(const QModelIndex &	parent = QModelIndex()) const override;
	QVariant	data(		const QModelIndex & index,										int role = Qt::DisplayRole) const override;
	QVariant	headerData(	int					section,	Qt::Orientation orientation,	int role = Qt::DisplayRole) const override;

	void		collectDbColumns();
	void		processValues();


	Q_INVOKABLE void		importCsv(const QString & csvFile);
	Q_INVOKABLE bool		importCsv(QTextStream & csvStream, QChar sepa = ';');
	Q_INVOKABLE void		clearColumns();
	Q_INVOKABLE int			columnWidthProvider(int col);
	Q_INVOKABLE int			rowHeightProvider(int row);

	QFont metricFont() const;
	void setMetricFont(const QFont & newMetricFont);

	int cellMargin() const;
	void setCellMargin(int newCellMargin);

signals:
	void	openingFileFailed(const QString & filename, const QString & error);
	void	metricFontChanged();
	void	cellMarginChanged();


private:
	ImportColumns			_columns;
	SchoolScannerTable	*	_table	= nullptr;
	Labels				*	_labels	= nullptr;

	QFont					_metricFont;
	QFontMetrics			_metrics;

	int						_maxWidthCol = 300,
							_cellMargin = 20;
};

#endif // IMPORTER_H
