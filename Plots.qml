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

		function onAllChanPlotChanged()
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

		SplitView.minimumHeight:		150
		SplitView.maximumHeight:		150


		onLoadingChanged: (loadRequest)=>
		{
			if(loadRequest.status === WebEngineView.LoadSucceededStatus)
			{					  
				runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.channelStatus))
				runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
			}
		}
		
		onWidthChanged:				runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
		onHeightChanged:			runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
	}
	
	Image
	{
		cache:						false
		source:						respiro.flowChartFile
		SplitView.preferredHeight:	parent.height * 0.5
		fillMode:					Image.PreserveAspectFit

		onWidthChanged:				R.plotWidth		= width
		onHeightChanged:			R.plotHeight	= height
	}


	StackLayout
	{
		id:						stack
		SplitView.fillHeight:	true
		
		WebEngineView
		{
			id:		allChanPlotView
			url:	"qrc:/plotly.html"
	
			onLoadingChanged: (loadRequest)=>
			{
				if(loadRequest.status === WebEngineView.LoadSucceededStatus)
				{
					runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.allChanPlot))
					runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
				}
			}
			
			onWidthChanged:				runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
			onHeightChanged:			runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
		}
	
		WebEngineView
		{
			id:		measTimePlotView
			url:	"qrc:/plotly.html"

			onLoadingChanged: (loadRequest)=>
			{
				if(loadRequest.status === WebEngineView.LoadSucceededStatus)
				{
					runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.measTimePlot))
					runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
				}
			}
			
			onWidthChanged:				runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
			onHeightChanged:			runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
		}
	
		WebEngineView
		{
			id:		groupChanPlotView
			url:	"qrc:/plotly.html"
	
			onLoadingChanged: (loadRequest)=>
			{
				if(loadRequest.status === WebEngineView.LoadSucceededStatus)
				{
					runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.groupChanPlot))
					runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
				}										   
			}
			
			onWidthChanged:				runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
			onHeightChanged:			runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
		}
	}
	
	Row
	{
		id:							rijtje
		SplitView.minimumHeight:	40
		SplitView.maximumHeight:	40
		
		Repeater
		{
			model:		["All channels", "Measurements over time", "Grouped channels" ]
			
			RectButton
			{
				text:				modelData
				implicitWidth:		rijtje.width / 3
				onClicked:			stack.currentIndex = index
				enabled:			stack.currentIndex !== index
			}
		}
		
		
	}
}

