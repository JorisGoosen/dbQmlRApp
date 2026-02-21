import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

SplitView
{
	orientation:	Qt.Vertical

	Tafel
	{
		model:						respiroDataProc

		columnWidthProvider:		respiroDataProc.columnWidthProvider
		rowHeightProvider:			respiroDataProc.rowHeightProvider

		//visible:					respiroDataProc.rowCount > 0
	}

	Tafel
	{
		model:						respiroDataMeas

		columnWidthProvider:		respiroDataMeas.columnWidthProvider
		rowHeightProvider:			respiroDataMeas.rowHeightProvider
		//SplitView.fillHeight:		true
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
	
	RowLayout
	{
		HWFeedbackButton
		{

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
			width:				temperaturePressureText.contentWidth  + generalMargin
			height:				temperaturePressureText.contentHeight + generalMargin
	
			Text
			{
				id:					temperaturePressureText
				text:				"<b>Temperature Respiro:</b>&nbsp;" + respiro.temp1 + "<sup>c</sup><br><b>Temperature Sample:</b>&nbsp;" + respiro.temp2 + "<sup>c</sup><br><b>Pressure:</b>&nbsp;" + respiro.pressure + "bar"
				anchors.centerIn:	parent
				color:				foregroundColor
			}
		}
	}
}
