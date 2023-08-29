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

		Text
		{
			text:			"Voer in:"
			font.family:	fontFamilie
		}

		TextField
		{
			id:					schoolType
			placeholderText:	"VO, MBO of ?"
			onTextChanged:		importer.schoolType = text
			font.family:		fontFamilie
		}

		TextField
		{
			id:					respondentType
			placeholderText:	"Docenten, Leerlingen of Studenten?"
			onTextChanged:		importer.type = text
			font.family:		fontFamilie
		}

		Text
		{
			font.family:	fontFamilie
			text:			"<i>nb. dit wordt enkel gebruikt als de ingelezen data niet vermeld om welke type school of respondent het gaat</i>"
		}
	}


	RectButton
	{
		id:			laadKnop
		text:		"Laad bestand"
		onClicked:	selecteerBestand.open()
		enabled:	respondentType.text !== "" && schoolType.text !== ""
		visible:	!importeerKnop.visible
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
