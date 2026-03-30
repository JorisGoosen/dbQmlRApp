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
		id:		channelStatusView
		url:	"qrc:/plotly.html"

		SplitView.fillHeight: true

		Connections
		{
			target:	respiro
			function onChannelStatusChanged(channelPlot)
			{
				channelStatusView.runJavaScript("Plotly.newPlot('het_plot', %1)".arg(channelPlot))
			}

		}

		onLoadingChanged: (loadRequest)=>
		{
			if(loadRequest.status === WebEngineView.LoadSucceededStatus)
				channelStatusView.runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.channelStatus))
		}
	}
	
	//Image
	//{
	//	source: "dummy.png"
	//	SplitView.preferredHeight: parent.height * 0.666667

	//	onWidthChanged:			R.plotWidth		= width
	//	onHeightChanged:		R.plotHeight	= height
	//}

}

