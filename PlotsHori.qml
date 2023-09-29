import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle
{
							id:				swiper
	property alias			model:			repeat.model
	property alias			modelFilters:	repeatFilter.model
	property list<real>		aspecten:		[]
	property list<int>		hoogtes:		[]
	property list<string>	titels:			[]
							clip:			true
							implicitHeight:	aspecten.length > tabBar.currentIndex ? aspecten[tabBar.currentIndex] * width : implicitHeight
							color:			controlBackgroundPlots
	Rectangle
	{
		id:					lijntje
		height:				dikkeLijnDikte
		color:				controlForegroundNeutral

		anchors
		{
			left:			parent.left
			top:			parent.top
			right:			parent.right
		}
	}

	Rectangle
	{
		id:					titelVak
		height:				titelTekst.implicitHeight + 8
		color:				controlBackgroundNeutral

		anchors
		{
			left:			parent.left
			top:			lijntje.bottom
			right:			parent.right
		}

		Text
		{
			id:		titelTekst
			text:	swiper.titels.length === 0 ? "???" : swiper.titels[Math.min(swiper.titels.length-1, tabBar.currentIndex)]

			font.family:			fontFamilie
			horizontalAlignment:	Text.AlignHCenter
			verticalAlignment:		Text.AlignVCenter
			color:					controlForegroundNeutral
			font.pixelSize:			30

			anchors
			{
				left:			parent.left
				top:			parent.top
				right:			parent.right
			}
		}
	}



	TabBar
	{
		id:		tabBar

		anchors
		{
			left:			parent.left
			top:			titelVak.bottom
			right:			parent.right
		}

		background: Rectangle {
			   color: controlForegroundNeutral
		   }

		Repeater
		{
			id:	repeatFilter

			TabButton
			{
				id:		tabButton
				text:	modelData === 'Geen' ? 'Geen filters' : modelData

				property bool selected: index === tabBar.currentIndex && tabBar.count > 1

				contentItem:	Text
				{
					color:						tabButton.selected ? controlForegroundFocus : controlForegroundNeutral
					text:						"<b>" + tabButton.text + "</b>"
					anchors.fill:				parent
					font.family:				fontFamilie
					horizontalAlignment:		Text.AlignHCenter
					verticalAlignment:			Text.AlignVCenter
				}

				background: Item {
					Rectangle
					{
							color:				tabButton.selected ? controlBackgroundFocus : controlBackgroundNeutral
							border.color:		tabButton.selected ? controlForegroundFocus : controlBackgroundNeutral
							border.width:		1
							anchors.fill:		parent
							anchors.margins:	dikkeLijnDikte / 2
					}
				}
			}
		}
	}

	StackLayout
	{
		id:					stackView
		clip:				true

		currentIndex:		tabBar.currentIndex
		Layout.fillHeight:	false
		Layout.fillWidth:	false
		Layout.alignment:	Qt.AlignTop

		Repeater
		{
			id:	repeat

			Image
			{
				source:				hoogtes[index] > 0 ? modelData : ""
				width:				stackView.width
				cache:				false
				fillMode:			Image.PreserveAspectFit
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
}