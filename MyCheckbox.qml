import QtQuick
import QtQuick.Controls.Basic

CheckBox 
{
	id: control
	contentItem: Text
	{
			 text: control.text
			 font: control.font
			 opacity: enabled ? 1.0 : 0.3
			 color: foregroundColor
			 verticalAlignment: Text.AlignVCenter
			 leftPadding: control.indicator.width + control.spacing
		 
	}
	
	
	
	indicator: Rectangle 
	{
			 implicitWidth: 26
			 implicitHeight: 26
			 x: control.leftPadding
			 y: parent.height / 2 - height / 2
			 radius: 30
			 border.color: foregroundColor
			 color:			backgroundColor
			 
	
			 Rectangle {
				 width: 14
				 height: 14
				 x: 6
				 y: 6
				 radius: 8
				 color: foregroundColor
				 visible: control.checked
			 }
		 }
}
