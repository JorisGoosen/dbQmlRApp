import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout
{
	id:					infoRow
	

	Text
	{
		text:			"<b>Last measurements:"
		color:			foregroundColor
		width:	parent.width; leftPadding:	2; rightPadding: 2;
	}

	
	GridLayout
	{
		width:		infoRow.width
		columns:	3
	
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
			horizontalAlignment:	Text.AlignRight
		}
		
		Item{}
		
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
			horizontalAlignment:	Text.AlignRight
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					"ppm"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
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
			horizontalAlignment:	Text.AlignRight
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					"ppm"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
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
			horizontalAlignment:	Text.AlignRight
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					"ppm"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
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
			horizontalAlignment:	Text.AlignRight
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					"ppm"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
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
			text:					respiro.flow.toFixed(2) 
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					"<sup>L/min</sup>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
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
			text:					respiro.tempRespiro.toFixed(1)
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					"<sup>c</sup>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
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
			text:					respiro.tempSample.toFixed(1)
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					"<sup>c</sup>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
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
			text:					respiro.pressure.toFixed(1)
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
		}

		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					"mBar"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
		}
	
		Item
		{
			Layout.fillHeight:	true
			Layout.columnSpan:	3
		}
		
		
		
	//GridLayout
	//{
	//	width:		infoRow.width
	//	columns:	2
		
		Text
		{
			Layout.alignment:		Qt.AlignLeft
			text:					"<b>Cycle time:</b>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					(respiro.channelRuntimeSec / 60).toFixed(2)
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					"min"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignLeft
			text:					"<b>Runtime:</b>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					(respiro.runtimeSec / (3600*24)).toFixed(2)
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					"days"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignLeft
			text:					"<b>Remaining:</b>"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					((respiro.runtimeTotalSec - respiro.runtimeSec) / (3600*24)).toFixed(2)
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
		}
		
		Text
		{
			Layout.alignment:		Qt.AlignRight
			text:					"days"
			color:					foregroundColor
			leftPadding:			2; rightPadding: 2;
			horizontalAlignment:	Text.AlignRight
		}
	}
}

