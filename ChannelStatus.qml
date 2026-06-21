import QtQuick 
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout
{
	required property int		channel
	required property int		channelID
	required property bool		leakPass
	required property bool		pressPass
	required property bool		volPass
	required property bool		measureStable
	required property int		cycle
	required property double	hsVolMl
	required property double	co2MaxPpm
	required property double	o2MinPerc
	required property double	o2MaxPerc
	required property double	ch4MaxPpm
	required property bool		isActive
	required property bool		inExperiment
	required property string	statusText
	required property string	statusColor
	
	width:				Math.max(90, implicitWidth)
	height:				implicitHeight
	
	implicitWidth:		100
	implicitHeight:		100
		
	Rectangle
	{
		z:						-1
		color:					statusColor
		border.color:			foregroundColor
		width:					40
		height:					40
		radius:					80
		
		Layout.alignment:		Qt.AlignHCenter
		
		Text
		{
			color:				foregroundColor
			text:				"Ch%1".arg(channelID)
			font.bold:			true
			anchors.centerIn:	parent
		}
		
		MouseArea
		{
			id:					channelMouse
			z:					100
			anchors.fill:		parent
			onClicked:			!respiro.controlWanted ? respiro.leakTest(channelID) : menu.open()
			acceptedButtons:	(respiro.controlWanted || !leakPass) && !respiro.running ? Qt.LeftButton : Qt.NoButton
			cursorShape:		(respiro.controlWanted || !leakPass) && !respiro.running ? (containsPress ? Qt.ClosedHandCursor : Qt.PointingHandCursor) : Qt.ArrowCursor
			hoverEnabled:		true
		}
		
		Menu 
		{
			id: menu
	
			MenuItem {
				text:			"Measure"
				onTriggered:	respiro.measure(channelID)
			}
			MenuItem {
				text:			"Leak Test"
				onTriggered:	respiro.leakTest(channelID)
			}
			MenuItem {
				text: "Flush"
				onTriggered:	respiro.flush(channelID)
			}
			
			MenuItem {
				text: "Opened Lid"
				onTriggered:	respiro.openedLid(channelID)
			}
			
			MenuItem {
				text: "Measure Headspace Post"
				onTriggered:	respiro.measureHeadspacePost(channelID)
			}
		}
		
		ToolTip.visible:		channelMouse.containsMouse
		ToolTip.delay:			200
		ToolTip.text:			"%11
Cycle %1
Sample volume: %2
CO2max_ppm: %3
O2min_perc: %4
O2max_perc: %5
CH4max_ppm: %6
Leak passed: %7
Volume passed: %8			
Pressure passed: %9
Measurements stable: %10
".		arg(cycle)		.
		arg(hsVolMl)	.
		arg(co2MaxPpm)	.
		arg(o2MinPerc)	.
		arg(o2MaxPerc)	.
		arg(ch4MaxPpm)	.
		arg(leakPass)	.
		arg(volPass)	.
		arg(pressPass)	.
		arg(measureStable) .
		arg(!respiro.controlWanted ? "Click to do a leaktest on this channel!" : "Manually control this channel via a menu!")
		
		
		
	}
	
	Text
	{
		color:		foregroundColor
		text:		statusText
		font.bold:	true
		
		Layout.alignment:	Qt.AlignHCenter
	}
	
	Item { Layout.fillHeight: true }
	
	//RectButton
	//{
	//	visible:				
	//}
	
}
		
	
	
