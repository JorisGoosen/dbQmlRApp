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

	HorizontalHeaderView
	{
		id:				horizontalHeader
		syncView:		mainTableView
		clip:			true
		anchors
		{
			top:		parent.top
			left:		mainTableView.left
			right:		parent.right
		}

		delegate: Rectangle
		{
			implicitWidth:	100
			implicitHeight: 50
			color:			"transparent"
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

	VerticalHeaderView
	{
		id:				verticalHeader
		syncView:		mainTableView
		clip:			true
		anchors
		{
			top:		mainTableView.top
			left:		parent.left
			bottom:		parent.bottom
		}

		delegate: Rectangle
		{
			implicitWidth:	100
			implicitHeight: 50
			color:			"transparent"
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

	TableView
	{
		id:		mainTableView
		clip:	true

		columnWidthProvider:	function() { return -1; }
		rowHeightProvider: 		function() { return -1; }

		anchors
		{
			top:	horizontalHeader.bottom
			left:	verticalHeader.right
			right:	parent.right
			bottom:	parent.bottom
		}

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
