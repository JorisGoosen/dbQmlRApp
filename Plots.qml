import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Image
{
	source:				plotPie ? plotPie.plotUrl : ""
	onSourceChanged:	console.log(source);
	cache:				false

	onWidthChanged:		R.plotWidth  = width
	onHeightChanged:	R.plotHeight = height
}
