#include "tablemodelfiltered.h"
#include "tablemodel.h"

TableModelFiltered::TableModelFiltered(TableModel * papa) : QSortFilterProxyModel(papa), _papa(papa)
{
	setSourceModel(_papa);
}

bool TableModelFiltered::filterAcceptsRow(int source_row, const QModelIndex & source_parent) const
{
	if(source_parent.isValid())
		return true;

	return _papa->rowAccepted(source_row);
}

int TableModelFiltered::columnWidthProvider(int col)
{
	return _papa->columnWidthProvider(mapToSource(index(0, col)).column());
}

int TableModelFiltered::rowHeightProvider(int row)
{
	return _papa->columnWidthProvider(mapToSource(index(row, 0)).row());
}

QFont TableModelFiltered::metricFont() const
{
	return _papa->metricFont();
}

int TableModelFiltered::cellMargin() const
{
	return _papa->cellMargin();
}

QPoint TableModelFiltered::topLeft() const
{
	return _papa->topLeft();
}

QPoint TableModelFiltered::bottomRight() const
{
	return _papa->bottomRight();
}

void TableModelFiltered::setMetricFont(const QFont & newMetricFont)
{
	_papa->setMetricFont(newMetricFont);
}

void TableModelFiltered::setCellMargin(int newCellMargin)
{
	_papa->setCellMargin(newCellMargin);
}

void TableModelFiltered::setTopLeft(QPoint newTopLeft)
{
	_papa->setTopLeft(newTopLeft);
}

void TableModelFiltered::setBottomRight(QPoint newBottomRight)
{
	_papa->setBottomRight(newBottomRight);
}


