import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtCore

ColumnLayout
{
	id:		column

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

	ChannelsSelector
	{
		id:				channels
		model:			respiro.channelInit
		implicitWidth:	column.width

		Layout.alignment: Qt.AlignHCenter
	}

	RowLayout
	{
		implicitHeight:		runtimeSec.implicitHeight
		implicitWidth:		column.width
		Layout.alignment:	Qt.AlignHCenter

		Text
		{
				text:					"Runtime: "
				color:					controlBackgroundNeutral
				Layout.alignment:		Qt.AlignVCenter
		}

		TextField
		{
			id:				runtimeSec
			text:			respiro.runtimeSec
			validator:		IntValidator { bottom: 0;}
			onTextChanged:
			{
				if(text !== "")
					respiro.runtimeSec = text
			}
		}

		Text
		{
			text:					"sec"
			color:					controlBackgroundNeutral
			Layout.alignment:		Qt.AlignVCenter
		}

		TextField
		{
			id:				runtimeHour
			text:			respiro.runtimeSec / 3600
			validator:		DoubleValidator { bottom: 0;}
			onTextChanged:
			{
				if(text !== "")
					respiro.runtimeSec = text * 3600
			}
		}

		Text
		{
			text:					"hour"
			color:					controlBackgroundNeutral
			Layout.alignment:		Qt.AlignVCenter
		}
	}

	RowLayout
	{
		implicitHeight:		channelRuntimeSec.height
		implicitWidth:		column.width
		Layout.alignment:	Qt.AlignHCenter

		Text
		{
			text:					"Channel runtime: "
			color:					controlBackgroundNeutral
			Layout.alignment:		Qt.AlignVCenter
		}

		TextField
		{
			id:				channelRuntimeSec
			text:			respiro.channelRuntimeSec
			validator:		IntValidator { bottom: 0;}
			onTextChanged:
			{
				if(text !== "")
					respiro.channelRuntimeSec = text
			}
		}

		Text
		{
			text:					"sec"
			color:					controlBackgroundNeutral
			Layout.alignment:		Qt.AlignVCenter
		}

		TextField
		{
			id:				channelRuntimeMin
			text:			respiro.channelRuntimeSec / 60
			validator:		DoubleValidator { bottom: 0;}
			onTextChanged:
			{
				if(text !== "")
					respiro.channelRuntimeSec = text * 60
			}
		}

		Text
		{
			text:					"minutes"
			color:					controlBackgroundNeutral
			Layout.alignment:		Qt.AlignVCenter
		}
	}

	Rectangle
	{
		id:					initCheckboxes
		implicitHeight:		calibrateCO2CheckBox.height
		implicitWidth:		boxesRow.implicitWidth
		Layout.alignment:	Qt.AlignHCenter

		color:				controlBackgroundNeutral
		border.color:		controlForegroundNeutral
		border.width:		1

		RowLayout
		{
			id:	boxesRow

			anchors
			{
				top:				parent.top
				bottom:				parent.bottom
				horizontalCenter:	parent.horizontalCenter
			}

			CheckBox
			{
				id:					calibrateCO2CheckBox
				text:				"calibrate CO2"
				checked:			respiro.calibrateCO2
				onCheckedChanged:	if(checked !== respiro.calibrateCO2) respiro.calibrateCO2 = checked;
			}

			CheckBox
			{
				text:				"Internal Leak Test"
				checked:			respiro.internalLeakTest
				onCheckedChanged:	if(checked !== respiro.internalLeakTest) respiro.internalLeakTest = checked;
			}

			CheckBox
			{
				text:				"Initial Hs Flush"
				checked:			respiro.initialHsFlush
				onCheckedChanged:	if(checked !== respiro.initialHsFlush) respiro.initialHsFlush = checked;
			}
		}
	}

	RectButton
	{
		text:		"Start Session"
		toolTip:	"Creates a folder with the datafiles etc for a respiro measurement cycle."
		onClicked:	respiro.startSession()
		Layout.alignment: Qt.AlignHCenter
	}

	RectButton
	{
		text:		"Load Previous Session"
		toolTip:	"Select a folder containing the files for a previous session to view the results"
		onClicked:	oldSessionSelector.open()
		Layout.alignment: Qt.AlignHCenter
	}
}
