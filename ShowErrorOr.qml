import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Rectangle
{
	id:							textRect
	
	color:						textArea.activeFocus		?  controlBackgroundFocus	: controlBackgroundNeutral
	border.color:				textArea.visible 
									? textArea.activeFocus	? "red"						: "darkRed" 
									: textArea.activeFocus	? controlForegroundFocus	: controlBackgroundNeutral
	border.width:				1
	
	property alias error:		textArea.text
	
	ScrollableTextArea 
	{
		id:				textArea
		color:			textArea.activeFocus ? "red" : "darkRed"
		visible:		text !== ""
		anchors.fill:	parent
		z:				100
	}

}
