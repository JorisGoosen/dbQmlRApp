import QtQuick 2
import QtQuick.Controls 2
import QtQuick.Layouts

ColumnLayout
{
	id:			column
	spacing:	10

	FileBrowser
	{
		id:				selecteerBestand
		nameFilters:	["CSV files (*.csv)"]
		onAccepted:		importer.importCsv(currentFile)
	}


	RowLayout
	{
		visible:	!importeerKnop.visible
		spacing:	10

		Layout.alignment:	Qt.AlignHCenter

		RectButton
		{
			id:			laadKnop
			text:		"Laad bestand"
			onClicked:	selecteerBestand.open()
		}

		MyCheckBox
		{
			id:					schoolTypeMBO
			checked:			importer.schoolType === "MBO"
			text:				"MBO"
			onCheckedChanged:
			{
				importer.schoolType = (checked ? "MBO" : "VO")
				respondentType.zetRespondentType();
			}

		}

		MyCheckBox
		{
			id:					respondentType
			checked:			importer.type === "Docenten"
			text:				"Docenten"
			onCheckedChanged:	zetRespondentType()

			function  zetRespondentType()
			{
				importer.type = (respondentType.checked ? "Docenten" : importer.schoolType === "MBO" ? "Studenten" : "Leerlingen")
			}
		}

		Text
		{
			color:					controlForegroundNeutral
			font.family:			fontFamilie
			text:					"<i> -&gt; enkel voor het aanvullen van ingelezen data waarin niet vermeld wordt om welke type school of respondent het gaat</i>"
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
		id:				importeerKnop
		text:			"Importeer bestand"
		onClicked:		importer.actuallyImport()
		visible:		importer && importer.canImport
		implicitWidth:	column.width
	}


}
