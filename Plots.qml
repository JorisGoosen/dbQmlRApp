import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Image
{
	source:		plotPie ? plotPie.plotUrl : ""

	onWidthChanged:		R.plotWidth  = width
	onHeightChanged:	R.plotHeight = height
}
