import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

SplitView
{
	id:				splitViewEnv
	orientation:	Qt.Horizontal
	
	
	handle:	SplitHendel
	{ 
		height:		splitViewEnv.height
		pressed:	SplitHandle.pressed
	}
	
	Item
	{
		implicitWidth:			500
		Layout.preferredWidth:	implicitWidth
		height:					parent.height
		
		ScrollableTextArea
		{
			id:					settingsText
			text:				mainModel.settingsCode
		
			textArea.onTextChanged:  mainModel.settingsCode = textArea.text;
			
			anchors
			{
				top:			parent.top
				left:			parent.left
				right:			parent.right
				bottom:			applySettings.top
			}
		}
		
		RectButton
		{
			id:		applySettings
			text:	qsTr("Apply settings")
			
			onClicked:	() => { mainModel.applySettings(picErrorRect.width, picErrorRect.height) }
			
			anchors
			{
				left:			parent.left
				right:			parent.right
				bottom:			parent.bottom
			}
		}
	}

	ShowErrorOr
	{
		id:						picErrorRect
		height:					parent.height
		Layout.fillWidth:		true
		error:					mainModel.envPicError
		
		Image
		{
			source:				mainModel.envPicSource
			anchors.fill:		parent
			cache:				false
		}
	}
	
}
