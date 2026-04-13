import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window
{
	id:			absoluteRoot
	width:		1280
	height:		720
	visible:	true
	color:		windowBackgroundColor

	onClosing:	mainModel.closing();
	//visibility:	Window.FullScreen
	
	Popup
	{
		id:				portSelector
		
		x:				absoluteRoot.width  / 2 - (width  / 2)
		y:				absoluteRoot.height / 2 - (height / 2)
		width:			600
		padding:		generalMargin
		z:				50
		modal:			false
		focus:			true
		visible:		respiro.availablePorts.length > 0 && respiro.chosenPort === ""
		closePolicy:	Popup.NoAutoClose
		
		onVisibleChanged:
		{
			console.log("port selector became " + (visible ? "" : "not ") + "visible")	
		}
		
		background:		Rectangle
		{
			color:			backgroundColor
			width:			portSelector.width
			height:			portSelector.height
			border.color:	foregroundColor
			border.width:	1
			radius:			8
		}
		
		contentItem: Column
		{
			id:				columnPorts
			z:				100
			width:			portSelector.width - generalMargin
			spacing:		generalMargin
			
			MyText
			{
				text:			"Please select the port to use below:"	
				implicitWidth:	columnPorts.width
			}
			
			Repeater
			{
				model:		respiro.availablePorts
				
				RectButton
				{
					implicitWidth:	columnPorts.width
					text:			modelData
					onClicked:		respiro.chosenPort = modelData
				}
				
			}
		}
	}

	Rectangle
	{
		z:				25
		color:			portSelector.visible ? "#000000"	: "transparent"
		opacity:		portSelector.visible ? 0.75			: 1.0
		visible:		portSelector.visible
		anchors.fill:	mainSplit
	}

	MySplitView
	{
		id:				mainSplit
		orientation:	Qt.Horizontal
		anchors.fill:	parent
		
		FocusScope
		{
			SplitView.fillWidth:	true
			
			TabBar
			{
				id:		tabBar
		
				anchors
				{
					top:	parent.top
					left:	parent.left
					right:	parent.right
				}
		
				onCurrentIndexChanged:	stack.currentIndex = currentIndex
		
				Repeater
				{
					model:	mainModel? mainModel.qmlsShown : []
		
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
		
			StackLayout
			{
				id:						stack
				clip:					true
				currentIndex:			1
				onCurrentIndexChanged:	tabBar.currentIndex = currentIndex
		
				Repeater
				{
					id:		swipeRepeater
					model:	mainModel? mainModel.qmlsShown : []
		
					onModelChanged:	tabBar.setCurrentIndex(0)
		
					Loader
					{
						id:				qmlLoader
						source:			modelData + ".qml"
					}
				}
		
				anchors
				{
					top:	tabBar.bottom
					left:	parent.left
					right:	parent.right
					bottom:	parent.bottom
				}
			}
		
		}
	
		Item
		{
			id:									hider
			property bool showMe:				respiro && respiro.backlog.length > 0
			SplitView.preferredWidth:			!showMe ? 0 : 500
			
			ListView
			{
				anchors
				{
					top:						parent.top
					left:						parent.left
					right:						parent.right					
					bottom:						smallLogoBox.top
					margins:					2
				}
				spacing:						2
				clip:							true
				visible:						hider.showMe
				model:							!hider.showMe ? [] : respiro.backlog
				delegate:						MyText 
				{ 
					text:						modelData;
					font.pixelSize:				9
					width:						ListView.view.width
					horizontalAlignment:		Text.AlignLeft
					//rectBack.anchors.margins:	generalMargin
				}
			}
			
			Rectangle
			{
				id:							smallLogoBox
				height:						2*generalMargin + (smallLogo.sourceSize.height / smallLogo.sourceSize.width) * smallLogo.width
				border.color:				foregroundColor
				border.width:				2
				color:						"#cccccc"
				
				Image
				{
					id:							smallLogo
					source:						"images/logo_biont_research.png"
					anchors.fill:				parent
					anchors.margins:			generalMargin
				}
					
				anchors
				{
					right:					parent.right					
					bottom:					parent.bottom
					left:					parent.left
				}
			}
		}
	}
}
