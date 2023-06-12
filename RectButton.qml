import QtQuick
import QtQuick.Controls

Rectangle
{
	id:	buttonRoot

	signal clicked();

	property alias text:		buttonText.text
	property string toolTip:	""

	implicitWidth:	buttonText.contentWidth  + generalMargin
	implicitHeight:	buttonText.contentHeight + generalMargin

	color:			buttonMouseArea.pressed ? controlBackgroundPressed : buttonMouseArea.containsMouse ? controlBackgroundFocus : controlBackgroundNeutral
	border.color:	buttonMouseArea.pressed ? controlForegroundPressed : buttonMouseArea.containsMouse ? controlForegroundFocus : controlForegroundNeutral
	border.width:	1
	radius:			4

	Text
	{
		id:					buttonText
		color:				buttonRoot.border.color
		anchors.centerIn:	parent
	}

	ToolTip.text:		toolTip
	ToolTip.timeout:	10000
	ToolTip.delay:		500
	ToolTip.visible:	toolTip !== "" && buttonMouseArea.containsMouse

	MouseArea
	{
		id:				buttonMouseArea
		anchors.fill:	parent
		onPressed:		buttonRoot.clicked()
		hoverEnabled:	true
	}
}
