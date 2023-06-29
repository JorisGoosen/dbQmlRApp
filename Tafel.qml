import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item
{
	property alias	model:				mainTableView.model
	property alias	columnWidthProvider:	mainTableView.columnWidthProvider
	property alias	rowHeightProvider:	mainTableView.rowHeightProvider
	property int	cellMargin:			0

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
			left:		mainTableScrollView.left
			right:		parent.right
		}

		delegate: Rectangle
		{
			color:			controlBackgroundNeutral
			border.color:	controlForegroundNeutral
			border.width:	1
			implicitHeight:	colText.height

			Text
			{
				id:						colText
				text:					display;
				//anchors.fill:			parent
				color:					controlForegroundNeutral
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
		//width:			importer.rowHeaderWidth

		anchors
		{
			top:		mainTableScrollView.top
			left:		parent.left
			bottom:		parent.bottom
		}

		delegate: Rectangle
		{
			color:			controlBackgroundNeutral
			border.color:	controlForegroundNeutral
			border.width:	1
			implicitWidth:	rowText.width

			Text
			{
				id:						rowText
				text:					display;
				//anchors.fill:			parent
				color:					controlForegroundNeutral
				wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
				horizontalAlignment:	Text.AlignHCenter
				verticalAlignment:		Text.AlignVCenter
				padding: 				generalMargin
				anchors
				{
					top:		parent.top
					bottom:		parent.bottom
					margins:	cellMargin / 2
				}
			}
		}
	}

	ScrollView
	{
		id:		mainTableScrollView

		anchors
		{
			top:	horizontalHeader.bottom
			left:	verticalHeader.right
			right:	parent.right
			bottom:	parent.bottom
		}

		TableView
		{
			id:		mainTableView
			clip:	true

			columnWidthProvider:	function() { return -1; }
			rowHeightProvider: 		function() { return -1; }

			onTopRowChanged:		importer.setTopLeft(	leftColumn,		topRow);
			onLeftColumnChanged:	importer.setTopLeft(	leftColumn,		topRow);
			onBottomRowChanged:		importer.setBottomRight(rightColumn,	bottomRow);
			onRightColumnChanged:	importer.setBottomRight(rightColumn,	bottomRow);



			delegate: Rectangle
			{
				color:			backgroundColor
				border.color:	controlForegroundNeutral
				border.width:	1
				Text
				{
					id:						itemText
					text:					display;
					anchors.fill:			parent
					color:					controlForegroundNeutral
					wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
					horizontalAlignment:	Text.AlignHCenter
					verticalAlignment:		Text.AlignVCenter
				}
			}
		}
	}
}
