import QtQuick 2
import QtQuick.Controls 2
import QtQuick.Layouts

Item
{
	property alias model: mainTableView.model

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
			border.color:	"yellow"
			border.width:	1
			Text
			{
				text:				display;
				anchors.centerIn:	parent
				color:				"yellow"
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
			border.color:	"yellow"
			border.width:	1
			Text
			{
				text:				display;
				anchors.centerIn:	parent
				color:				"yellow"
			}
		}
	}

	TableView
	{
		id:		mainTableView
		clip:	true

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
			border.color:	"yellow"
			border.width:	1
			Text
			{
				text:				display;
				anchors.centerIn:	parent
				color:				"yellow"
			}
		}
	}
}
