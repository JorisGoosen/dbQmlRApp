import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

SplitView
{
	orientation:	Qt.Horizontal
	
	
	handle:	SplitHandle{}
	
	
	ScrollableTextArea
	{
		id:						walkersText
		text:					mainModel.walkersCode
		Layout.preferredWidth:	Math.min(mainWindow.width/2,	300)
		
		function onTextChanged(newText)
		{
			mainModel.settingsCode = newText	
		}
	}

	Rectangle
	{
		id:						picRect
		
		color:					textArea.activeFocus ? controlBackgroundFocus : controlBackgroundNeutral
		border.color:			textArea.activeFocus ? controlForegroundFocus : controlBackgroundNeutral
		border.width:			1
		Layout.fillWidth:		true
		
		Image
		{
			source:				mainModel.envPicSource
			anchors.fill:		parent
		}
	}
	
}
