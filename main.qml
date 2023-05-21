import QtQuick 2.15
import QtQuick.Controls 2.15

Window
{

	width:		1280
	height:		720
	visible:	true
	color:		"#A06"


	TabBar
	{
		id:		tabBar

		anchors
		{
			top:	parent.top
			left:	parent.left
			right:	parent.horizontalCenter
		}

		Repeater
		{
			model:	plots

			TabButton
			{
				text:	modelData
			}
		}
	}

	SwipeView
	{
		id:					swiper
		clip:				true
		currentIndex:		tabBar.currentIndex
		onWidthChanged:		R.plotWidth		= width
		onHeightChanged:	R.plotHeight	= height

		onCurrentIndexChanged: if(tabBar.currentIndex != currentIndex)	tabBar.currentIndex = currentIndex

		Repeater
		{
			model:	plots

			Image
			{
				id:		plotImg
				source:	plotFolder + "/" + modelData
				cache:	false
			}
		}

		anchors
		{
			top:	tabBar.bottom
			left:	parent.left
			right:	parent.horizontalCenter
			bottom:	parent.verticalCenter
		}
	}

	ScrollView
	{
		id:				outputText
		contentWidth:	width


		Text
		{
			width:		outputText.width
			text:		R.prevOutputConcat
			color:		"yellow"
			wrapMode:	Text.Wrap

		}

		anchors
		{
			top:	parent.verticalCenter
			left:	parent.left
			right:	parent.horizontalCenter
			bottom:	inputText.top
		}
	}

	Item
	{

		anchors
		{
			top:	parent.top
			left:	parent.horizontalCenter
			right:	parent.right
			bottom:	inputText.top
		}

		HorizontalHeaderView
		{
			id:				horizontalHeader
			syncView:		mainTableView
			clip:			true
			anchors
			{
				top:		parent.top
				left:		mainTableView.left
				right:		parent.right
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

		VerticalHeaderView
		{
			id:				verticalHeader
			syncView:		mainTableView
			clip:			true
			anchors
			{
				top:		mainTableView.top
				left:		parent.left
				bottom:		parent.bottom
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

		TableView
		{
			id:		mainTableView
			model:	mainTable
			clip:	true

			anchors
			{
				top:	horizontalHeader.bottom
				left:	verticalHeader.right
				right:	parent.right
				bottom:	parent.bottom
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

		onEditingFinished: R.runRCommand(text)
	}

}
