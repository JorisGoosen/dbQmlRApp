import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtWebEngine


MySplitView
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

		SplitView.minimumHeight:		130
		SplitView.preferredHeight:		150
		SplitView.maximumHeight:		180


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
		sourceSize.width:			width * 2
		sourceSize.height:			height * 2

		onWidthChanged:				R.plotWidth		= width
		onHeightChanged:			R.plotHeight	= height
		
		SplitView.minimumHeight:		130
	}


	StackLayout
	{
		id:						stack
		SplitView.fillHeight:	true
		
		SplitView.minimumHeight:		200
		
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

	TabBar
	{
		id:							tabBar

		SplitView.minimumHeight:	40
		SplitView.maximumHeight:	40

		onCurrentIndexChanged:		stack.currentIndex = currentIndex

		Repeater
		{
			model:	["All channels", "Measurements over time", "Grouped channels" ]

			TabButton
			{
				id:		tabButton
				text:	modelData

				property bool selected: index === tabBar.currentIndex

				contentItem:	Text
				{
					color:				tabButton.selected ? controlBackgroundPressed : controlBackgroundNeutral
					text:				tabButton.text
					anchors.centerIn:	parent
				}

				background: Rectangle
				{
						color:	tabButton.selected ? controlForegroundPressed : controlForegroundNeutral
				}
			}
		}
	}
	
	
}

