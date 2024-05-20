import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Rectangle
{
	id:							textRect
	
	color:						textArea.activeFocus ? controlBackgroundFocus : controlBackgroundNeutral
	border.color:				textArea.activeFocus ? controlForegroundFocus : controlBackgroundNeutral
	border.width:				1
	
	property alias text:		textArea.text
	property TextArea textArea:	textArea
	
	signal textChanged(string newText)
	
	ScrollView 
	{
		id:					textView
		anchors.fill:		parent
   
		TextArea 
		{
			id:				textArea
			color:			foregroundColor
			
			function onTextChanged()
			{
				textRect.textChanged(text);	
			}
		}
	}
}
