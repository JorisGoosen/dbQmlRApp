import QtQuick 2
import QtQuick.Controls 2
import QtQuick.Layouts

Item
{
	property alias model:				mainTableView.model
	property alias columnWidthProvider:	mainTableView.columnWidthProvider
	property alias rowHeightProvider:	mainTableView.rowHeightProvider

	width:			implicitWidth
	height:			implicitHeight
	implicitWidth:	mainTableView.implicitWidth		+ verticalCenter.implicitWidth
	implicitHeight:	mainTableView.implicitHeight	+ horizontalHeader.implicitHeight

	Text
	{
		id:						metricFontSetter
		visible:				false
		Component.onCompleted:	mainTableView.model.metricFont = metricFontSetter.font
	}
	
	Rectangle
	{
		anchors
		{
			top:		parent.top
			left:		parent.left
			right:		parent.right
			bottom:		horizontalHeader.bottom
		}
		
		color:			backgroundColor
		z:				-10
	}

	HorizontalHeaderView
	{
		id:				horizontalHeader
		syncView:		mainTableView
		clip:			true
		reuseItems:		true
		anchors
		{
			top:		parent.top
			left:		scrollviewHier.left
			right:		parent.right
		}

		delegate: Rectangle
		{
			implicitWidth:	headerText.contentWidth + model.cellMargin
			implicitHeight: 50
			color:			backgroundHColor
			border.color:	foregroundHColor
			border.width:	1

			Text
			{
				id:						headerText
				text:					display;
				anchors.centerIn:		parent
				textFormat:				Text.RichText
				color:					foregroundHColor
				wrapMode:				Text.NoWrap
				horizontalAlignment:	Text.AlignHCenter
				verticalAlignment:		Text.AlignVCenter
				height:					contentHeight  + generalMargin
			}
		}
	}

	Rectangle
	{
		anchors.fill:	verticalHeader
		color:			backgroundColor
		z:				-10
	}

	
	VerticalHeaderView
	{
		id:				verticalHeader
		syncView:		mainTableView
		clip:			true
		reuseItems:		true
		anchors
		{
			top:		scrollviewHier.top
			left:		parent.left
			bottom:		parent.bottom
		}

		delegate: Rectangle
		{
			implicitWidth:	100
			implicitHeight: 50
			color:			backgroundHColor
			border.color:	foregroundHColor
			border.width:	1
			
			Text
			{
				text:					display;
				anchors.centerIn:		parent
				color:					foregroundHColor
				wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
				horizontalAlignment:	Text.AlignHCenter
				verticalAlignment:		Text.AlignVCenter
				height:					contentHeight  + generalMargin
				anchors
				{
					left:		parent.left
					right:		parent.right
					margins:	model.cellMargin / 2
				}
			}
		}
	}
	
	Rectangle
	{
		anchors.fill:	scrollviewHier
		color:			"transparent"
		border.color:	foregroundHColor
		border.width:	1
		z:				-10
	}

	ScrollView
	{
		id:			scrollviewHier
		anchors
		{
			top:	horizontalHeader.bottom
			left:	verticalHeader.right
			right:	parent.right
			bottom:	parent.bottom
		}
		
		TableView
		{
			id:				mainTableView
			clip:			true
			reuseItems:		true
	
			columnWidthProvider:	function() { return -1; }
			rowHeightProvider: 		function() { return -1; }
	

	
			delegate: Rectangle
			{
				implicitWidth:	100
				implicitHeight: 50
				color:			"transparent"
				border.color:	foregroundColor
				border.width:	1
	
				Text
				{
					text:					display;
					anchors.centerIn:		parent
					color:					foregroundColor
					wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
					horizontalAlignment:	Text.AlignHCenter
					verticalAlignment:		Text.AlignVCenter
					height:					contentHeight  + generalMargin
					anchors
					{
						left:		parent.left
						right:		parent.right
						margins:	model.cellMargin / 2
					}
				}
			}
		}
	}
}
