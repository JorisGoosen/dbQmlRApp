import QtQuick 2
import QtQuick.Controls 2
import QtQuick.Layouts

Item
{
	property alias model:				mainTableView.model
	property alias columnWidthProvider:	mainTableView.columnWidthProvider
	property alias rowHeightProvider:	mainTableView.rowHeightProvider

	Text
	{
		id:						metricFontSetter
		visible:				false
		Component.onCompleted:	importer.metricFont = metricFontSetter.font
	}

	HorizontalHeaderView
	{
		id:				horizontalHeader
		syncView:		mainTableView
		clip:			true
		//height:			importer.columnHeaderHeight

		anchors
		{
			top:		parent.top
			left:		mainTableView.left
			right:		parent.right
		}

		delegate: Rectangle
		{
			color:			"transparent"
			border.color:	"yellow"
			border.width:	1
			implicitHeight:	colText.height

			Text
			{
				id:						colText
				text:					display;
				//anchors.fill:			parent
				color:					"yellow"
				wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
				horizontalAlignment:	Text.AlignHCenter
				verticalAlignment:		Text.AlignVCenter
				height:					contentHeight  + generalMargin
				anchors
				{
					left:		parent.left
					right:		parent.right
					margins:	importer.cellMargin / 2
				}
			}
		}
	}

	VerticalHeaderView
	{
		id:				verticalHeader
		syncView:		mainTableView
		clip:			true
		//width:			importer.rowHeaderWidth

		anchors
		{
			top:		mainTableView.top
			left:		parent.left
			bottom:		parent.bottom
		}

		delegate: Rectangle
		{
			color:			"transparent"
			border.color:	"yellow"
			border.width:	1
			implicitWidth:	rowText.width

			Text
			{
				id:						rowText
				text:					display;
				//anchors.fill:			parent
				color:					"yellow"
				wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
				horizontalAlignment:	Text.AlignHCenter
				verticalAlignment:		Text.AlignVCenter
				width:					rowText.contentWidth  + generalMargin
				anchors
				{
					top:		parent.top
					bottom:		parent.bottom
					margins:	importer.cellMargin / 2
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
			color:			"transparent"
			border.color:	"yellow"
			border.width:	1
			Text
			{
				id:						itemText
				text:					display;
				anchors.fill:			parent
				color:					"yellow"
				wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
				horizontalAlignment:	Text.AlignHCenter
				verticalAlignment:		Text.AlignVCenter
			}
		}
	}
}
