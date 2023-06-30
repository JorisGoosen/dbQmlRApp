import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window
{

	width:		1280
	height:		720
	visible:	true
	color:		windowBackgroundColor

	onClosing:	mainModel.closing();


	TabBar
	{
		id:		tabBar

		anchors
		{
			top:	parent.top
			left:	parent.left
			right:	parent.right
		}

		onCurrentIndexChanged:	stack.currentIndex = currentIndex

		Repeater
		{
			model:	mainModel? mainModel.qmlsShown : []

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

	StackLayout
	{
		id:						stack
		clip:					true
		currentIndex:			1
		onCurrentIndexChanged:	tabBar.currentIndex = currentIndex

		Repeater
		{
			id:		swipeRepeater
			model:	mainModel? mainModel.qmlsShown : []

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
}
