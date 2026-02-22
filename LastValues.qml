import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout
{
	id:					infoRow
	implicitHeight:     childrenRect.height
	
	property real uniformWidth: ((width-spacing) / 8) - spacing
	
	MyText
	{
		text:			"<b>Last measurements</b>: "
		implicitWidth:	uniformWidth
	}
	
	MyText
	{
		text:			"<b>CO<sub>2</sub>:</b>&nbsp;" + respiro.CO2.toFixed(2)
		implicitWidth:	uniformWidth
	}
	
	MyText
	{
		text:			"<b>CH<sub>4</sub>:</b>&nbsp;" + respiro.CH4.toFixed(2)
		implicitWidth:	uniformWidth
	}
	
	MyText
	{
		text:			"<b>O<sub>2</sub>:</b>&nbsp;" + respiro.O2.toFixed(3) + "%"
		implicitWidth:	uniformWidth
	}
	
	MyText
	{
		text:			"<b>Temp. Respiro:</b>&nbsp;" + respiro.tempRespiro.toFixed(1) + "<sup>c</sup>"
		implicitWidth:	uniformWidth
	}
	
	MyText
	{
		text:			"<b>Temp. Sample:</b>&nbsp;" + respiro.tempSample.toFixed(1) + "<sup>c</sup>"
		implicitWidth:	uniformWidth
	}
	
	MyText
	{
		text:			"<b>Pressure:</b>&nbsp;" + respiro.pressure.toFixed(1) + " mBar"
		implicitWidth:	uniformWidth
	}
	
	MyText
	{
		text:		"<b>Current channel:</b>&nbsp;" + respiro.curChannel
		implicitWidth:	uniformWidth
	}
}

