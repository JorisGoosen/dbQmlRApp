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

	RowLayout
	{
		Text
		{
			text:			"Voer in:"
		}

		TextField
		{
			id:					schoolType
			placeholderText:	"VO, MBO of ?"
			onTextChanged:		importer.schoolType = text
		}

		TextField
		{
			id:					respondentType
			placeholderText:	"Docenten, Leerlingen of Studenten?"
			onTextChanged:		importer.type = text
		}

		Text
		{
			text:	"<i>nb. dit wordt enkel gebruikt als de ingelezen data niet vermeld om welke type school of respondent het gaat</i>"
		}
	}


	RectButton
	{
		id:			importButton
		text:		"Importeer bestand"
		onClicked:	selecteerBestand.open()
		enabled:	respondentType.text !== "" && schoolType.text !== ""
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
