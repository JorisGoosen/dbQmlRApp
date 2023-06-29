#include "abstractsizeprovidertable.h"

AbstractSizeProviderTable::AbstractSizeProviderTable(QObject *parent)
	: QAbstractTableModel{parent}, _metrics(_metricFont)
{

}


int AbstractSizeProviderTable::columnWidthProvider(int col)
{
	QRect maxBounds(0,0, _maxWidthCol, std::numeric_limits<int>::max());

	QString header = headerData(col, Qt::Horizontal).toString();


	QRect bounds = _metrics.boundingRect(maxBounds, Qt::TextWordWrap, header);

	int largestVal = bounds.width();

	for(int row=std::max(0, _topLeft.y() - _sizeScan); row<std::min(rowCount(), _bottomRight.y() + _sizeScan); row++)
		largestVal = std::max(largestVal, _metrics.boundingRect(maxBounds, Qt::TextWordWrap, data(index(row, col)).toString()).width());

	return std::min(largestVal, _maxWidthCol) + _cellMargin;
}

int AbstractSizeProviderTable::rowHeightProvider(int row)
{
	QRect maxBounds(0,0, _maxWidthCol, std::numeric_limits<int>::max());

	QString header = headerData(row, Qt::Vertical).toString();

	QRect bounds = _metrics.boundingRect(maxBounds, Qt::TextWordWrap, header);

	int largestVal = bounds.height();

	for(int column=std::max(0, _topLeft.x() - _sizeScan); column<std::min(columnCount(), _bottomRight.x() + _sizeScan); column++)
	{
		const QString & val = data(index(row, column)).toString();
		largestVal = std::max(largestVal, _metrics.boundingRect(maxBounds, Qt::TextWordWrap, val).height());
	}

	return largestVal + _cellMargin;
}

QFont AbstractSizeProviderTable::metricFont() const
{
	return _metricFont;
}

void AbstractSizeProviderTable::setMetricFont(const QFont & newMetricFont)
{
	if (_metricFont == newMetricFont)
		return;
	_metricFont = newMetricFont;
	emit metricFontChanged();

	_metrics = QFontMetrics(_metricFont);
}

int AbstractSizeProviderTable::cellMargin() const
{
	return _cellMargin;
}

void AbstractSizeProviderTable::setCellMargin(int newCellMargin)
{
	if (_cellMargin == newCellMargin)
		return;
	_cellMargin = newCellMargin;
	emit cellMarginChanged();
}


QPoint AbstractSizeProviderTable::topLeft() const
{
	return _topLeft;
}

void AbstractSizeProviderTable::setTopLeft(QPoint newTopLeft)
{
	if (_topLeft == newTopLeft)
		return;
	_topLeft = newTopLeft;

	//std::cout << "topLeft is: " << _topLeft.x() << ", " << _topLeft.y() << std::endl;

	emit topLeftChanged();
}

QPoint AbstractSizeProviderTable::bottomRight() const
{
	return _bottomRight;
}


void AbstractSizeProviderTable::setBottomRight(QPoint newBottomRight)
{
	if (_bottomRight == newBottomRight)
		return;
	_bottomRight = newBottomRight;

	//std::cout << "bottomRight is: " << _bottomRight.x() << ", " << _bottomRight.y() << std::endl;

	emit bottomRightChanged();
}
