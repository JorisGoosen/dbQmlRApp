import QtQuick 2
import QtQuick.Controls 2
import QtQuick.Layouts

ColumnLayout
{
	FileBrowser
	{
		id:				selecteerBestand
		nameFilters:	["CSV files (*.csv)"]
		onAccepted:		mainModel.importCSV(currentFile)
	}

	RectButton
	{
		id:			importButton
		text:		"Importeer bestand"
		onClicked:	selecteerBestand.open()
	}

	Tafel
	{
		model:	mainModel.importModel
	}


}
