import QtQuick 2.15

Window
{

	width:		1280
	height:		720
	visible:	true
	color:		"purple"

	Text
	{
		id:	outputText
		text:	"?"
		color:	"yellow"
		anchors
		{
			top:	parent.top
			left:	parent.left
			right:	parent.horizontalCenter
			bottom:	inputText.top
		}
	}

	TableView
	{
		id:		mainTableView
		model:	mainTable

		anchors
		{
			top:	parent.top
			left:	parent.horizontalCenter
			right:	parent.right
			bottom:	inputText.top
		}

		delegate: Rectangle
		{
			implicitWidth:	100
			implicitHeight: 50
			color:			"transparent"
			border.color:	"yellow"
			border.width:	1
			Text
			{
				text:				display;
				anchors.centerIn:	parent
				color:				"yellow"
			}
		}
	}

	TextInput
	{
		id:			inputText
		height:		Math.max(contentHeight, 20)

		text:	"?"
		color:	"yellow"

		anchors
		{
			left:	parent.left
			right:	parent.right
			bottom:	parent.bottom
		}

		onEditingFinished: outputText.text = R.runRCommand(text)
	}

}
