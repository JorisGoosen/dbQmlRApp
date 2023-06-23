import QtQuick 2
import QtQuick.Controls 2
import QtQuick.Layouts

ColumnLayout
{
	id:		columns

	FileBrowser
	{
		id:				selecteerBestand
		nameFilters:	["CSV files (*.csv)"]
		onAccepted:		importer.importCsv(currentFile)
	}

	RectButton
	{
		id:			importButton
		text:		"Importeer bestand"
		onClicked:	selecteerBestand.open()
	}

	Tafel
	{
		model:					importer
		columnWidthProvider:	importer.columnWidthProvider
		rowHeightProvider:		importer.rowHeightProvider

		implicitWidth:	columns.width
		implicitHeight:	(columns.height / 3) * 2
	}


}
