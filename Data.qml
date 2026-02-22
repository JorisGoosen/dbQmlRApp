import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

SplitView
{
	orientation:	Qt.Horizontal

	SplitView
	{
		orientation:			Qt.Vertical
		SplitView.fillWidth:	true
	
		Tafel
		{
			model:						respiroDataProc
	
			columnWidthProvider:		respiroDataProc.columnWidthProvider
			rowHeightProvider:			respiroDataProc.rowHeightProvider
			
			SplitView.preferredHeight: parent.height * 0.4
	
			//visible:					respiroDataProc.rowCount > 0
		}
	
		Tafel
		{
			model:						respiroDataMeas
	
			columnWidthProvider:		respiroDataMeas.columnWidthProvider
			rowHeightProvider:			respiroDataMeas.rowHeightProvider
			//SplitView.fillHeight:		true
			SplitView.preferredHeight: parent.height * 0.5
			//visible:					respiroDataMeas.rowCount > 0
		}
	
		//Image
		//{
		//	source: "dummy.png"
		//	SplitView.preferredHeight: parent.height * 0.666667
	
		//	onWidthChanged:			R.plotWidth		= width
		//	onHeightChanged:		R.plotHeight	= height
		//}
	
		//Tafel
		//{
		//	model:						respiroMsgs
	
		//	columnWidthProvider:		respiroMsgs.columnWidthProvider
		//	rowHeightProvider:			respiroMsgs.rowHeightProvider
	
		//	SplitView.minimumHeight:	model.rowCount > 0 ? 200 : 0
		//	SplitView.preferredHeight:	parent.height * 0.333333
		//	//visible:					respiroMsgs.rowCount > 0
		//}
		Item
		{
				
			implicitHeight:			infoRow.implicitHeight
			implicitWidth:			parent.width
			
			SplitView.minimumHeight: infoRow.implicitHeight
			SplitView.maximumHeight: infoRow.implicitHeight
			
			RowLayout
			{
				id:					infoRow
				implicitHeight:		childrenRect.height
				
				MyText
				{
					text:			qsTr("Last measurements: ")
					height:			co2Button.height
				}
				
				HWFeedbackButton
				{
					id:				co2Button
					text:			"CO2"
					value:			respiro.CO2
					checked:		respiro.CO2On
		
					onClicked:		(newChecked)=>{ respiro.CO2On = newChecked; }
				}
		
				HWFeedbackButton
				{
		
					text:			"CH4"
					value:			respiro.CH4
					checked:		respiro.CH4On
		
					onClicked:		(newChecked)=>{ respiro.CH4On = newChecked; }
				}
		
				HWFeedbackButton
				{
		
					text:			"O2"
					value:			respiro.O2
					checked:		respiro.O2On
		
					onClicked:		(newChecked)=>{ respiro.O2On = newChecked; }
				}	
				
				Rectangle
				{
					id:					temperaturePressureBox
					color:				backgroundColor
					border.color:		foregroundColor
					border.width:		1
					width:				temperaturePressureText.contentWidth  + 2*generalMargin
					height:				parent.height //temperaturePressureText.contentHeight + generalMargin
			
					Text
					{
						id:					temperaturePressureText
						text:				"<b>Temperature Respiro:</b>&nbsp;" + respiro.tempRespiro.toFixed(2) + "<sup>c</sup><br><b>Temperature Sample:</b>&nbsp;" + respiro.tempSample.toFixed(2) + "<sup>c</sup><br><b>Pressure:</b>&nbsp;" + respiro.pressure + "mBar"
						anchors.centerIn:	parent
						color:				foregroundColor
					}
				}
				
				Rectangle
				{
					id:					channelbox
					color:				backgroundColor
					border.color:		foregroundColor
					border.width:		1
					width:				channelText.contentWidth  + 2*generalMargin
					height:				parent.height //temperaturePressureText.contentHeight + generalMargin
			
					Text
					{
						id:					channelText
						text:				"<b>Current channel:</b>&nbsp;" + respiro.curChannel
						anchors.centerIn:	parent
						color:				foregroundColor
					}
				}
				
			}
		}
	}
	
	ListView
	{
		SplitView.preferredWidth: 500
		
		model:		respiro.backlog
		delegate:	MyText 
		{ 
			text:					modelData;
			font.pixelSize:			9
			width:					ListView.view.width
			horizontalAlignment:	Text.AlignLeft
		}
	}
}
