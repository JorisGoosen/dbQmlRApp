import QtQuick 2
import QtQuick.Controls 2
import QtQuick.Layouts
import Qt.labs.platform

Item
{
	ColumnLayout
	{
		spacing:			20
		anchors.centerIn:	parent



		RectButton
		{
			text:				"Laad database '%1'".arg(mainModel.dbPathKort)
			toolTip:			"Dit is de database die je vorige keer gebruikt hebt"
			onClicked:			mainModel.loadDatabase()
			visible:			mainModel.dbPath !== ""
			Layout.fillWidth:	true
		}



		RectButton
		{
			text:				"Laad een bestaande database"
			toolTip:			"Staat waarschijnlijk in je dropbox/cloudmap"
			onClicked:			selecteerBestaandeDatabase.open()
			Layout.fillWidth:	true
		}

		FileBrowser
		{
			id:					selecteerBestaandeDatabase
			nameFilters:		["SQLite files (*.sqlite)"]
			onAccepted:			mainModel.selectDatabase(currentFile)
		}




		RectButton
		{
			text:				"Maak een nieuwe database"
			toolTip:			"Voor die verse start"
			onClicked:			selecteerNieuweDatabase.open()
			Layout.fillWidth:	true
		}

		FileBrowser
		{
			id:					selecteerNieuweDatabase
			nameFilters:		["SQLite files (*.sqlite)"]
			onAccepted:			mainModel.selectDatabase(currentFile)
			fileMode:			FileDialog.SaveFile
		}

	}

}
