import QtQuick 2
import QtQuick.Controls 2
import QtQuick.Layouts

ColumnLayout
{
	id:		column

	FileBrowser
	{
		id:				selecteerBestand
		nameFilters:	["CSV files (*.csv)"]
		onAccepted:		importer.importCsv(currentFile)
	}

	RowLayout
	{
		visible:	!importeerKnop.visible

		RectButton
		{
			id:			laadKnop
			text:		"Laad bestand"
			onClicked:	selecteerBestand.open()
			visible:	!importeerKnop.visible
		}

		MyCheckBox
		{
			id:					schoolType
			checked:			importer.schoolType === "MBO"
			text:				"MBO"
			onCheckedChanged:	importer.schoolType = checked ? "MBO" : "VO"

		}

		MyCheckBox
		{
			id:					respondentType
			checked:			importer.type === "Docenten"
			text:				"Docenten"
			onCheckedChanged:	importer.type = checked ? "Docenten" : "Leerlingen"
		}

		Text
		{
			font.family:	fontFamilie
			text:			"<i>nb. dit wordt enkel gebruikt als de ingelezen data niet vermeld om welke type school of respondent het gaat</i>"
		}


	}




	Tafel
	{
		model:					importer
		columnWidthProvider:	importer.columnWidthProvider
		rowHeightProvider:		importer.rowHeightProvider
		cellMargin:				importer.cellMargin

		implicitWidth:			column.width

		Layout.fillHeight:		true
	}

	RectButton
	{
		id:			importeerKnop
		text:		"Importeer bestand"
		onClicked:	importer.actuallyImport()
		visible:	importer && importer.canImport
	}


}
