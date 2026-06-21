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
		
		//function onChannelStatusChanged()
		//{
		//	channelStatusView.runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.channelStatus))
		//}

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
	
	ChannelStatusses
	{
		SplitView.minimumHeight:		90
		SplitView.preferredHeight:		90
		SplitView.maximumHeight:		130
		Layout.fillWidth:				true
	}
	
	//WebEngineView
	//{
	//	id:		channelStatusView
	//	url:	"qrc:/plotly.html"

	//	SplitView.minimumHeight:		110
	//	SplitView.preferredHeight:		150
	//	SplitView.maximumHeight:		180


	//	onLoadingChanged: (loadRequest)=>
	//	{
	//		if(loadRequest.status === WebEngineView.LoadSucceededStatus)
	//		{					  
	//			runJavaScript("Plotly.newPlot('het_plot', %1)".arg(respiro.channelStatus))
	//			runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
	//		}
	//	}
	//	
	//	onWidthChanged:				runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
	//	onHeightChanged:			runJavaScript("resizePlot(%1,%2)".arg(width).arg(height))
	//}
	
	
	MySplitView
	{
		orientation:	Qt.Horizontal
		
		SplitView.minimumHeight:		130
		SplitView.preferredHeight:		parent.height * 0.75
		
		LinkerOverzicht
		{
			SplitView.minimumWidth:		100
			SplitView.preferredWidth:	160
		}
		
		Image
		{
			
			cache:						false
			source:						respiro.flowChartFile
			
			fillMode:					Image.PreserveAspectFit
			sourceSize.width:			width 
			sourceSize.height:			height
	
			//onWidthChanged:			R.plotWidth		= width
			//onHeightChanged:			R.plotHeight	= height
			SplitView.minimumWidth:		100
			SplitView.fillWidth:		true
		}
		
		RechterOverzicht
		{
			SplitView.minimumWidth:		140
			SplitView.preferredWidth:	160
		}
	}

	StackLayout
	{
		id:						stack
		SplitView.fillHeight:	true
		
		SplitView.minimumHeight:		100
		
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
				height:	30

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

