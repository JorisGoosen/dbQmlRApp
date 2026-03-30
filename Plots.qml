import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtWebEngine


SplitView
{
	orientation:			Qt.Vertical
	SplitView.fillWidth:	true

	Connections
	{
		target:	respiro
		
		function onChannelStatusChanged()
		{
			channelStatusView.runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.channelStatus))
		}

		function onAllChanPlotStatusChanged()
		{
			allChanPlotView.runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.allChanPlot))
		}

		function onMeasTimePlotChanged()
		{
			measTimePlotView.runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.measTimePlot))
		}

		function onGroupChanPlotChanged()
		{
			groupChanPlotView.runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.groupChanPlot))
		}
	}

	
	WebEngineView
	{
		id:		channelStatusView
		url:	"qrc:/plotly.html"

		


		onLoadingChanged: (loadRequest)=>
		{
			if(loadRequest.status === WebEngineView.LoadSucceededStatus)
				channelStatusView.runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.channelStatus))
		}
	}


	WebEngineView
	{
		id:		allChanPlotView
		url:	"qrc:/plotly.html"

		SplitView.fillHeight: true
		SplitView.minimumnHeight:		100

		onLoadingChanged: (loadRequest)=>
		{
			if(loadRequest.status === WebEngineView.LoadSucceededStatus)
				allChanPlotView.runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.allChanPlot))
		}
	}

	WebEngineView
	{
		id:		measTimePlotView
		url:	"qrc:/plotly.html"

		SplitView.minimumnHeight:		100


		onLoadingChanged: (loadRequest)=>
		{
			if(loadRequest.status === WebEngineView.LoadSucceededStatus)
				measTimePlotView.runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.measTimePlot))
		}
	}

	WebEngineView
	{
		id:		groupChanPlotView
		url:	"qrc:/plotly.html"

		SplitView.minimumnHeight:		100

		onLoadingChanged: (loadRequest)=>
		{
			if(loadRequest.status === WebEngineView.LoadSucceededStatus)
				groupChanPlotView.runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.groupChanPlot))
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

