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
		: nameCSV(nameCSV), nameDB(nameDB)
	{}

	ImportColumn(const ColumnDefinition * cd, QStringList values)
		: importMe(cd), nameCSV(cd->friendlyName()), nameDB(cd->dbName()), values(values), cd(cd)
	{}

	void setCD(const ColumnDefinition * cdNew)
	{
		cd			= cdNew;
		importMe	= cd;
		nameDB		= importMe ? cd->dbName() : "";
	}

	bool						importMe = false;
	QString						nameCSV,
								nameDB;
	QStringList					values;
	const ColumnDefinition	*	cd = nullptr;
};

typedef std::vector<ImportColumn*> ImportColumns;

class Importer : public QAbstractTableModel
{
	Q_OBJECT

	Q_PROPERTY(QFont	metricFont			READ metricFont			WRITE setMetricFont			NOTIFY metricFontChanged		)
	Q_PROPERTY(int		cellMargin			READ cellMargin			WRITE setCellMargin			NOTIFY cellMarginChanged		)
	Q_PROPERTY(QString	schoolType			READ schoolType			WRITE setSchoolType			NOTIFY schoolTypeChanged		)
	Q_PROPERTY(QString	type				READ type				WRITE setType				NOTIFY typeChanged				)
	Q_PROPERTY(QPoint	topLeft				READ topLeft			WRITE setTopLeft			NOTIFY topLeftChanged			)
	Q_PROPERTY(QPoint	bottomRight			READ bottomRight		WRITE setBottomRight		NOTIFY bottomRightChanged		)


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

	QFont	metricFont()	const;
	int		cellMargin()	const;
	QString schoolType()	const;
	QString type()			const;
	QPoint	topLeft()		const;
	QPoint	bottomRight()	const;


public slots:


	void setMetricFont(	const QFont & newMetricFont);
	void setCellMargin(	int newCellMargin);
	void setSchoolType(	const QString & newSchoolType);
	void setType(		const QString & newType);
	void setTopLeft(	QPoint newTopLeft);
	void setTopLeft(	int col, int row)				{	setTopLeft(QPoint(col, row)); }
	void setBottomRight(QPoint newBottomRight);
	void setBottomRight(int col, int row)				{	setBottomRight(QPoint(col, row)); }


signals:
	void	openingFileFailed(const QString & filename, const QString & error);
	void	metricFontChanged();
	void	cellMarginChanged();
	void	schoolTypeChanged();
	void	typeChanged();
	void	topLeftChanged();
	void	bottomRightChanged();






private:
	ImportColumns			_columns;
	SchoolScannerTable	*	_table	= nullptr;
	Labels				*	_labels	= nullptr;

	QFont					_metricFont;
	QFontMetrics			_metrics;

	int						_maxWidthCol	= 300,
							_cellMargin		= 20,
							_sizeScan		= 10;	///< how many extravisible cells should be taken into account when calculating cellsize?
	QString					_schoolType,
							_type;
	QPoint					_topLeft,
							_bottomRight;
};

#endif // IMPORTER_H
