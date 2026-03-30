import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtWebEngine


SplitView
{
	orientation:			Qt.Vertical
	SplitView.fillWidth:	true

	
	WebEngineView
	{
		url: "file://dummy.png"
	}
	
	//Image
	//{
	//	source: "dummy.png"
	//	SplitView.preferredHeight: parent.height * 0.666667

	//	onWidthChanged:			R.plotWidth		= width
	//	onHeightChanged:		R.plotHeight	= height
	//}

}

