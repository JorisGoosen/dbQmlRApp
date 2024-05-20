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
	

	ScrollView 
	{
		id:						textView
		anchors.fill:			parent
		clip:					true
		
		FontMetrics
		{
			id:					measureMe
			font:				textArea.font
		}
   
		TextArea 
		{
			id:					textArea
			color:				foregroundColor
			tabStopDistance:	4 * measureMe.averageCharacterWidth
		}
	}
}
