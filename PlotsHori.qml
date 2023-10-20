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
	property list<string>	bestanden:		[]
	property list<string>	bestandenAbs:	[]
							clip:			true
							implicitHeight:	aspecten.length > tabBar.currentIndex ? tabBar.y + tabBar.height + bodemVak.height + aspecten[tabBar.currentIndex] * width : implicitHeight
							color:			controlBackgroundPlots

							onModelChanged: console.log(model)
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

			MyTabButton
			{
				id:			tabButton
				text:		modelData === 'Geen' || modelData === 'Type' ? 'Geen filters' : modelData
				selected:	index === tabBar.currentIndex && tabBar.count > 1
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
				onVisibleChanged:	console.log(modelData)
			}
		}

		anchors
		{
			top:	tabBar.bottom
			left:	parent.left
			right:	parent.right
			bottom:	bodemVak.top
		}
	}

	RectButton
	{
						id:			bodemVak
						groot:		false
						text:		swiper.bestanden.length === 0 ? "???" : swiper.bestanden[curIndex]
		property int	curIndex:	Math.min(swiper.bestanden.length-1, tabBar.currentIndex)

						onClicked:	if(swiper.bestanden.length > 0) mainModel.showInFolder(swiper.bestandenAbs[curIndex])

		anchors
		{
			left:			parent.left
			bottom:			parent.bottom
			right:			parent.right
		}
	}
}
