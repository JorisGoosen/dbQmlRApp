import QtQuick
import QtQuick.Controls
import QtQuick.Layouts



ListView
{
	id:			lijstje
	model:		plotList


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
