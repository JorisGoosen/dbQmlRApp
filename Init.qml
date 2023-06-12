import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtCore

ColumnLayout
{
	Layout.alignment: Qt.AlignHCenter

	FolderDialog
	{
		id:					oldSessionSelector
		acceptLabel:		"Select old session folder"
		currentFolder:		StandardPaths.standardLocations(StandardPaths.AppDataLocation)[0]
		options:			FolderDialog.ReadOnly
		onAccepted:			respiro.loadOldSession(currentFolder)

	}

	MessageDialog
	{
		id:			selectedOldFolderWrong
		text:		"Couldn't find respiro.sqlite in your selected folder '" + respiro.outputFolder + "', make sure you select the right folder."
		buttons:	MessageDialog.Ok

	}

	Connections
	{
		target:		respiro
		function	onCantFindOldDatabase() { selectedOldFolderWrong.open(); }
	}

	RectButton
	{
		text:		"Start Session"
		toolTip:	"Creates a folder with the datafiles etc for a respiro measurement cycle."
		onClicked:	respiro.startSession()
	}

	RectButton
	{
		text:		"Load Previous Session"
		toolTip:	"Select a folder containing the files for a previous session to view the results"
		onClicked:	oldSessionSelector.open()
	}
}
