import QtQuick 2.15
import QtQuick.Controls 2.15

Window
{

	width:		1280
	height:		720
	visible:	true
	color:		windowBackgroundColor


	TabBar
	{
		id:		tabBar

		anchors
		{
			top:	parent.top
			left:	parent.left
			right:	parent.right
		}

		Repeater
		{
			model:	mainModel.qmlsShown

			TabButton
			{
				id:		tabButton
				text:	modelData

				property bool selected: index === tabBar.currentIndex

				contentItem:	Text
				{
					color:				tabButton.selected ? controlBackgroundPressed : controlBackgroundNeutral
					text:				tabButton.text
					anchors.centerIn:	parent
				}

				background: Rectangle
				{
						color:	tabButton.selected ? controlForegroundPressed : controlForegroundNeutral
				}
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

		Repeater
		{
			id:		swipeRepeater
			model:	mainModel.qmlsShown

			onModelChanged:	tabBar.setCurrentIndex(0)

			Loader
			{
				id:				qmlLoader
				source:			modelData + ".qml"
			}
		}

		anchors
		{
			top:	tabBar.bottom
			left:	parent.left
			right:	parent.right
			bottom:	parent.bottom
		}
	}

	readonly property Item _toolTipOverrideItem: Item
	{
		//These properties override those for ALL attached ToolTips in the application
		//ToolTip.toolTip shouldn't be changed anywhere else otherwise we get hard to debug behaviour
		ToolTip.toolTip.background:		Rectangle { color: backgroundColor; border.width: 1; border.color: foregroundColor }
		ToolTip.toolTip.contentItem:	Text
		{
			//font:			jaspTheme.font
			wrapMode:		Text.WrapAtWordBoundaryOrAnywhere
			text:			ToolTip.toolTip.text
		}
		ToolTip.toolTip.z:						1234
	}

	/*
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
			syncView:		respiroTableView
			clip:			true
			anchors
			{
				top:		parent.top
				left:		respiroTableView.left
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
			syncView:		respiroTableView
			clip:			true
			anchors
			{
				top:		respiroTableView.top
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
			id:		respiroTableView
			model:	respiroData
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

	readonly property Item _toolTipOverrideItem: Item
	{
		//These properties override those for ALL attached ToolTips in the application
		//ToolTip.toolTip shouldn't be changed anywhere else otherwise we get hard to debug behaviour
		ToolTip.toolTip.background:		Rectangle { color: backgroundColor; border.width: 1; border.color: foregroundColor }
		ToolTip.toolTip.contentItem:	Text
		{
			//font:			jaspTheme.font
			wrapMode:		Text.WrapAtWordBoundaryOrAnywhere
			text:			ToolTip.toolTip.text
		}
		ToolTip.toolTip.z:						1234
	}

	/*


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
	*/
}
