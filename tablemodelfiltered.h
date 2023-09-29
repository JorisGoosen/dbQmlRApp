#ifndef TABLEMODELFILTERED_H
#define TABLEMODELFILTERED_H

#include <QSortFilterProxyModel>
#include <QPoint>
#include <QFont>
Q_MOC_INCLUDE("tablemodel.h")

class TableModel;
class TableModelFiltered : public QSortFilterProxyModel
{
	Q_OBJECT
	Q_PROPERTY(QFont	metricFont			READ metricFont			WRITE setMetricFont			NOTIFY metricFontChanged		)
	Q_PROPERTY(int		cellMargin			READ cellMargin			WRITE setCellMargin			NOTIFY cellMarginChanged		)
	Q_PROPERTY(QPoint	topLeft				READ topLeft			WRITE setTopLeft			NOTIFY topLeftChanged			)
	Q_PROPERTY(QPoint	bottomRight			READ bottomRight		WRITE setBottomRight		NOTIFY bottomRightChanged		)

public:
	TableModelFiltered(TableModel * papa);

	bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

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


private:
	TableModel * _papa;
};

#endif // TABLEMODELFILTERED_H
