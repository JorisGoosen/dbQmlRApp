import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtCore

Item
{	
	
	ColumnLayout
	{
		id:					column
		height:				parent.height
		width:				Math.min(parent.width, 800)
		
		anchors.centerIn:	parent
	
		FileDialog
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
		
		Item
		{
			Layout.fillHeight:	true	
			implicitWidth:		parent.width
			
			Image
			{
				source:				"images/logo_biont_research.png"	
				width:				sourceSize.width * 0.5
				height:				sourceSize.height * 0.5
				anchors.centerIn:	parent
			}
			
		}
	
		ChannelsSelector
		{
			id:				channels
			model:			respiro.channelInit
			implicitWidth:	parent.width
	
			Layout.alignment: Qt.AlignHCenter
		}
		
		
		Rectangle
		{
			id:					initCheckboxes
			implicitHeight:		calibrateCO2CheckBox.height
			implicitWidth:		parent.width
			Layout.alignment:	Qt.AlignHCenter
	
			color:				controlBackgroundNeutral
			border.color:		controlForegroundNeutral
			border.width:		1
	
			RowLayout
			{
				id:	boxesRow
	
				anchors
				{
					verticalCenter:		parent.verticalCenter
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
		
		
		Rectangle
		{
			Layout.alignment:	Qt.AlignHCenter
	
			color:				"#222222"
			border.color:		controlBackgroundNeutral
			border.width:		1
		
			implicitHeight:		channelRuntimeSec.height + generalMargin*2
			implicitWidth:		parent.width
	
			Text
			{
				text:					"Channel runtime: "
				color:					controlBackgroundNeutral
				
				anchors
				{
					verticalCenter:	parent.verticalCenter
					right:			channelRuntimeSec.left
					rightMargin:	generalMargin
				}
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
				anchors
				{
					top:			parent.top
					right:			channelRuntimeSecSec.left
					bottom:			parent.bottom
					margins:		generalMargin
				}
			}
	
			Text
			{
				id:					channelRuntimeSecSec
				text:				"sec"
				color:				controlBackgroundNeutral
				
				anchors
				{
					verticalCenter:	parent.verticalCenter
					right:			parent.horizontalCenter
					rightMargin:	generalMargin
				}
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
				anchors
				{
					top:			parent.top
					left:			parent.horizontalCenter
					bottom:			parent.bottom
					margins:		generalMargin
				}
			}
	
			Text
			{
				text:					"minutes"
				color:					controlBackgroundNeutral
				Layout.alignment:		Qt.AlignVCenter
				anchors
				{
					verticalCenter:	parent.verticalCenter
					left:			channelRuntimeMin.right
					leftMargin:		generalMargin
				}
			}
		}
		
	
		Rectangle
		{
			Layout.alignment:	Qt.AlignHCenter
	
			color:				"#222222"
			border.color:		controlBackgroundNeutral
			border.width:		1
			
			implicitHeight:		runtimeSec.implicitHeight + generalMargin*2
			implicitWidth:		parent.width
	
			Text
			{
					text:					"Total runtime: "
					color:					controlBackgroundNeutral
					
					anchors
					{
						verticalCenter:	parent.verticalCenter
						right:			runtimeSec.left
						rightMargin:	generalMargin
					}
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
				
				anchors
				{
					top:			parent.top
					right:			runtimeSecSec.left
					bottom:			parent.bottom
					margins:		generalMargin
				}
			}
	
			Text
			{
				id:					runtimeSecSec
				text:				"sec"
				color:				controlBackgroundNeutral
				
				anchors
				{
					verticalCenter:	parent.verticalCenter
					right:			parent.horizontalCenter
					rightMargin:	generalMargin
				}
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
				
				anchors
				{
					top:			parent.top
					left:			parent.horizontalCenter
					bottom:			parent.bottom
					margins:		generalMargin
				}
			}
	
			Text
			{
				text:					"hour"
				color:					controlBackgroundNeutral
				Layout.alignment:		Qt.AlignVCenter
				anchors
				{
					left:			runtimeHour.right
					verticalCenter:	parent.verticalCenter
					leftMargin:		generalMargin
				}
			}
		}
	
		RectButton
		{
			text:				"Start Session"
			toolTip:			"Creates a folder with the datafiles etc for a respiro measurement cycle."
			onClicked:			respiro.startSession()
			Layout.alignment:	Qt.AlignHCenter
			implicitWidth:		parent.width
		}
		
		Item
		{
			Layout.fillHeight: true	
		}
	
		RectButton
		{
			id:					prevButton
			text:				"Load Previous Session"
			toolTip:			"Select a folder containing the files for a previous session to view the results"
			onClicked:			oldSessionSelector.open()
			Layout.alignment:	Qt.AlignHCenter
			implicitWidth:		parent.width
		}
		
		Item
		{
			height:		prevButton.height	
		}
	}
}
