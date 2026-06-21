import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout
{
	id:					infoRow
	

	ColumnLayout
	{
		width:		parent.width
	
		Text
		{
			text:			"<b>DB:"
			color:			foregroundColor
			width:	parent.width; leftPadding:	2; rightPadding: 2;
		}
		
		TextArea
		{
			text:			respiro.dbPath
			font:			"monospace"
			color:			foregroundColor
			width:			parent.width
			wrapMode:		Text.WrapAtWordBoundaryOrAnywhere
			readOnly:		true
			selectByMouse:	true	
			leftPadding:	2; 
			rightPadding:	2;
		}
		
		Text
		{
			text:			"<b>Last measurements:"
			color:			foregroundColor
			width:	parent.width; leftPadding:	2; rightPadding: 2;
		}
	}
	
	
	GridLayout
	{
		width:		parent.width
		columns:	2
	
		Text
		{
			Layout.alignment:		Qt.AlignLeft
			text:					"<b>Channel</b>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					respiro.curChannel
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignLeft
			text:					"<b>CO<sub>2</sub>:</b>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					respiro.CO2.toFixed(2)
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignLeft
			text:					"<b>CO<sub>2</sub>ADC:</b>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					respiro.CO2ADC.toFixed(2)
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignLeft
			text:					"<b>CH<sub>4</sub>:</b>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					respiro.CH4.toFixed(2)
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignLeft
			text:					"<b>O<sub>2</sub></b>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					respiro.O2.toFixed(2)
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignLeft
			text:					"<b>Flow:</b>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					respiro.flow.toFixed(2)  + "<sup>L/min</sup>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}

		Text
		{
			Layout.alignment:		Qt.AlignLeft
			text:					"<b>RTemp:</b>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					respiro.tempRespiro.toFixed(1) + "<sup>c</sup>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}

		Text
		{
			Layout.alignment:		Qt.AlignLeft
			text:					"<b>STemp:</b>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					respiro.tempSample.toFixed(1) + "<sup>c</sup>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}

		Text
		{
			Layout.alignment:		Qt.AlignLeft
			text:					"<b>Pressure:</b>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					respiro.pressure.toFixed(1)  + " mBar"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
	}
	
	ColumnLayout
	{
		width:		parent.width
		
		Item
		{
			Layout.fillHeight:	true	
		}
		
		Text
		{
			text:			"<b>Cycle time:</b>&nbsp;%1 min".arg((respiro.channelRuntimeSec / 60).toFixed(2))
			
			color:			foregroundColor
			width:	parent.width; leftPadding:	2; rightPadding: 2;
		}
		
		Text
		{
			text:			"<b>Total runtime:</b>&nbsp;%1 days".arg(respiro.runtimeSec / (3600*24).toFixed(2))
			color:			foregroundColor
			width:	parent.width; leftPadding:	2; rightPadding: 2;
		}
		
		Text
		{
			text:			"<b>Remaining runtime:</b>&nbsp;%1 days".arg((respiro.runtimeTotalSec - respiro.runtimeSec) / (3600*24).toFixed(2))
			color:			foregroundColor
			width:	parent.width; leftPadding:	2; rightPadding: 2;
		}
	}
}

