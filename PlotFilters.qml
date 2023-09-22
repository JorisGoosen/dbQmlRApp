import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item
{
	property string basePlotPath: ""

	TabBar
	{
		id:					tabBar

		Repeater
		{
			model:		mainModel.plotFilterNames

			TabButton
			{
				id:		tabButton
				text:	modelData

				property bool selected: index == tabBar.currentIndex

				contentItem:	Text
				{
					color:						tabButton.selected ? controlForegroundFocus : controlForegroundNeutral
					text:						"<b>" + tabButton.text + "</b>"
					font.family:				fontFamilie
					anchors.fill:				parent
					horizontalAlignment:		Text.AlignHCenter
					verticalAlignment:			Text.AlignVCenter
				}

				background: Rectangle
				{
						color:	tabButton.selected ? controlBackgroundFocus : controlBackgroundNeutral
				}
			}
		}
	}

	Image
	{
		id:					stackView
		source:				basePlotPath + mainModel.plotFilterNames[tabBar.currentIndex].toLowerCase() + ".png"
	}
}
