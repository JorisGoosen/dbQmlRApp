#ifndef ABSTRACTSIZEPROVIDERTABLE_H
#define ABSTRACTSIZEPROVIDERTABLE_H

#include <QFont>
#include <QFontMetrics>
#include <QAbstractTableModel>

class AbstractSizeProviderTable : public QAbstractTableModel
{
	Q_OBJECT

	Q_PROPERTY(QFont	metricFont			READ metricFont			WRITE setMetricFont			NOTIFY metricFontChanged		)
	Q_PROPERTY(int		cellMargin			READ cellMargin			WRITE setCellMargin			NOTIFY cellMarginChanged		)
	Q_PROPERTY(QPoint	topLeft				READ topLeft			WRITE setTopLeft			NOTIFY topLeftChanged			)
	Q_PROPERTY(QPoint	bottomRight			READ bottomRight		WRITE setBottomRight		NOTIFY bottomRightChanged		)

public:
	explicit AbstractSizeProviderTable(QObject *parent = nullptr);

	Q_INVOKABLE int			columnWidthProvider(int col);
	Q_INVOKABLE int			rowHeightProvider(int row);

	QFont	metricFont()	const;
	int		cellMargin()	const;
	QPoint	topLeft()		const;
	QPoint	bottomRight()	const;


public slots:
	void setMetricFont(	const QFont & newMetricFont);
	void setCellMargin(	int newCellMargin);
	void setTopLeft(	QPoint newTopLeft);
	void setTopLeft(	int col, int row)				{	setTopLeft(QPoint(col, row)); }
	void setBottomRight(QPoint newBottomRight);
	void setBottomRight(int col, int row)				{	setBottomRight(QPoint(col, row)); }


signals:
	void	metricFontChanged();
	void	cellMarginChanged();
	void	topLeftChanged();
	void	bottomRightChanged();

protected:
	QFont					_metricFont;
	QFontMetrics			_metrics;
	int						_maxWidthCol	= 300,
							_cellMargin		= 20,
							_sizeScan		= 10;	///< how many extravisible cells should be taken into account when calculating cellsize?
	QPoint					_topLeft,
							_bottomRight;

};

#endif // ABSTRACTSIZEPROVIDERTABLE_H
