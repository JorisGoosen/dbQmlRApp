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
		anchors.fill:	parent
		clip:			true

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
}
