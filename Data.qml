import QtQuick 2
import QtQuick.Controls 2
import QtQuick.Layouts

ColumnLayout
{
	id:		column

	property alias model:				tafel.model
	property alias columnWidthProvider:	tafel.columnWidthProvider
	property alias rowHeightProvider:	tafel.rowHeightProvider
	property alias cellMargin:			tafel.cellMargin

	Tafel
	{
		id:						tafel
		model:					schoolScannerTable
		columnWidthProvider:	schoolScannerTable.columnWidthProvider
		rowHeightProvider:		schoolScannerTable.rowHeightProvider
		cellMargin:				schoolScannerTable.cellMargin

		implicitWidth:			column.width
		Layout.fillHeight:		true
	}
}
