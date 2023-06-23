import QtQuick 2.15
import QtQuick.Controls 2.15

Window
{

	width:		1280
	height:		720
	visible:	true
	color:		windowBackgroundColor

	Component.onCompleted: importer.cellMargin = Qt.binding(function(){return generalMargin;});


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

				property bool selected: index == tabBar.currentIndex

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

		onCurrentIndexChanged: if(tabBar.currentIndex != currentIndex)	tabBar.currentIndex = currentIndex

		Repeater
		{
			id:		swipeRepeater
			model:	mainModel.qmlsShown

			Loader
			{
				id:				qmlLoader
				source:			modelData + ".qml"
				width:			swiper.width
				height:			swiper.height
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
