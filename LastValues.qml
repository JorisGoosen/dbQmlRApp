import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout
{
	id:					infoRow
	clip:				true

	property real uniformWidth: width
	
	Text
	{
		text:			"<b>DB:"
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
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
		text:			"<b>Last measurements:<br>Channel </b>&nbsp;%1".arg(respiro.curChannel)
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
	}
	
	Text
	{
		text:			"<b>CO<sub>2</sub>:</b>&nbsp;" + respiro.CO2.toFixed(2)
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
	}
	
	Text
	{
		text:			"<b>CO<sub>2</sub>ADC:</b>&nbsp;" + respiro.CO2ADC.toFixed(2)
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
	}
	
	Text
	{
		text:			"<b>CH<sub>4</sub>:</b>&nbsp;" + respiro.CH4.toFixed(2)
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
	}
	
	Text
	{
		text:			"<b>O<sub>2</sub>:</b>&nbsp;" + respiro.O2.toFixed(3) + "%"
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
	}
	
	Text
	{
		text:			"<b>Flow:</b>&nbsp;" + respiro.flow.toFixed(2) + "<sup>L/min</sup>"
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
	}
	
	
	Text
	{
		text:			"<b>RTemp:</b>&nbsp;" + respiro.tempRespiro.toFixed(1) + "<sup>c</sup>"
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
	}
	
	Text
	{
		text:			"<b>STemp:</b>&nbsp;" + respiro.tempSample.toFixed(1) + "<sup>c</sup>"
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
	}
	
	Text
	{
		text:			"<b>Pressure:</b>&nbsp;" + respiro.pressure.toFixed(1) + " mBar"
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
	}
	
	Item
	{
		Layout.fillHeight:	true	
	}
	
	Text
	{
		text:			"<b>Cycle time:</b>&nbsp;%1 min".arg((respiro.channelRuntimeSec / 60).toFixed(2))
		
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
	}
	
	Text
	{
		text:			"<b>Total runtime:</b>&nbsp;%1 days".arg(respiro.runtimeSec / (3600*24).toFixed(2))
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
	}
	
	Text
	{
		text:			"<b>Remaining runtime:</b>&nbsp;%1 days".arg((respiro.runtimeTotalSec - respiro.runtimeSec) / (3600*24).toFixed(2))
		color:			foregroundColor
		leftPadding:		2; rightPadding:		2;
	}
}

