import QtQuick
import QtQuick.Controls

ScrollBar
{
	id:				balk
	//hoverEnabled:	true

	implicitWidth:	18
	implicitHeight: 18

	background: Rectangle
	{
		color:			controlBackgroundNeutral
		border.width:	2
		border.color:	controlForegroundNeutral
	}

	contentItem: Rectangle
	{
		color:			balk.active /*? controlForegroundPressed : balk.hovered*/ ? controlForegroundFocus : controlForegroundNeutral
		border.width:	4
		border.color:	balk.active /*? controlBackgroundPressed : balk.hovered*/ ? controlBackgroundFocus : controlBackgroundNeutral
	}
}
