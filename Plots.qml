import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle
{
	color: controlForegroundNeutral

	ListView
	{
		id:				lijstje
		model:			plotList
		spacing:		generalMargin
		clip:			true

		anchors
		{
			top:		parent.top
			left:		parent.left
			right:		parent.right
			bottom:		verseGrafieken.top
		}

		delegate: PlotsHori
		{
			width:				ListView.view.width
			model:				display
			modelFilters:		filters
			aspecten:			aspectData
			hoogtes:			hoogteData
			titels:				titelData
			bestanden:			bestandData
			bestandenAbs:		bestandAbsData
		}



	}

	RectButton
	{
		id:						verseGrafieken
		text:					"Maak verse grafieken"
		toolTip:				"Kan even duren..."
		onClicked:				plotList.renderPlots()

		anchors
		{
			left:		parent.left
			right:		parent.right
			bottom:		parent.bottom
		}
	}
}
