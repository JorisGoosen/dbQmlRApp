import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item
{
	id:						column
	clip:					true
	width:					parent.width

	property var	model:	null

	function enlargeMe()
	{
		splitView.fillThisOne = model
	}

	SplitView.fillHeight:		splitView.fillThisOne === model
	SplitView.minimumHeight:	titleText.height

	RectButton
	{
		id:						titleText
		text:					column.model ? column.model.title : "???"
		width:					parent.width
		groot:					false
		onClicked:				column.enlargeMe()

	}

	ListView
	{
		id:						list
		clip:					true
		model:					column.model ? column.model : null

		anchors
		{
			top:				titleText.bottom
			left:				parent.left
			right:				parent.right
			bottom:				parent.bottom
			margins:			generalMargin
		}

		delegate:
			MyCheckBox
			{
				id:					control
				checked:			model.checkState
				text:				model.display
				onCheckedChanged:	model.checkState = checked
				width:				ListView.view.width
			}

		ScrollBar.vertical: Scrollbalk {}
	}
}
