 import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ListView
{
	model:	plotList

	delegate:	Image
	{
		source:				display
		cache:				false
		fillMode:			Image.PreserveAspectFit

		width:				ListView.view.width

		//onWidthChanged:		R.plotWidth  = width
		//onHeightChanged:	R.plotHeight = height
	}
}
