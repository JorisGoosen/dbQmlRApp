import QtQuick 2
import QtQuick.Controls 2
import QtQuick.Layouts

ColumnLayout
{
	id:		column

	Tafel
	{
		model:					schoolScannerTable
		columnWidthProvider:	schoolScannerTable.columnWidthProvider
		rowHeightProvider:		schoolScannerTable.rowHeightProvider
		cellMargin:				schoolScannerTable.cellMargin

		implicitWidth:			column.width

		Layout.fillHeight:		true
	}
}
