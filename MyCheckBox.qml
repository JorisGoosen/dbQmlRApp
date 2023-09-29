import QtQuick
import QtQuick.Controls

CheckBox
{
	id:					control

	padding: 			10

	background: Rectangle
	{
			 implicitWidth:		100
			 implicitHeight:	40
			 opacity:			enabled ? 1 : 0.3
			 color:				control.activeFocus ? controlBackgroundFocus : controlBackgroundNeutral
	}



	contentItem:	Text
	{
		text:				control.text
		font:				control.font
		opacity:			enabled ? 1.0 : 0.3
		color:				control.activeFocus ? controlForegroundFocus : controlForegroundNeutral
		verticalAlignment:	Text.AlignVCenter
		leftPadding:		control.indicator.width + control.spacing
	}

	indicator: Rectangle
	{
			 implicitWidth:		26
			 implicitHeight:	26
			 x:					control.leftPadding
			 y:					parent.height / 2 - height / 2
			 radius:			4
			 border.color:		control.activeFocus ? controlForegroundFocus : controlForegroundNeutral
			 border.width:		4
			 color:				"transparent"

			 Rectangle
			 {
				 width:		14
				 height:	14
				 x:			6
				 y:			6
				 radius:	2
				 color:		control.activeFocus ? controlForegroundFocus : controlForegroundNeutral
				 visible:	control.checked
			 }
		 }


}
