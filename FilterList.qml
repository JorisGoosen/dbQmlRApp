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

	Text
	{
		id:						titleText
		color:					controlForegroundNeutral
		font.family:			fontFamilie
		wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
		horizontalAlignment:	Text.AlignHCenter
		verticalAlignment:		Text.AlignVCenter
		padding: 				5
		text:					column.model ? column.model.title : "???"

		anchors
		{
			horizontalCenter:	parent.horizontalCenter
		}

		MouseArea
		{
			anchors.fill:		parent
			onClicked:			column.enlargeMe()
		}
	}

	ListView
	{
		id:						list
		clip:					true
		model:					column.model ? column.model : null

		anchors
		{
			left:				parent.left
			right:				parent.right
			bottom:				parent.bottom
			top:				titleText.bottom
			margins:			generalMargin
		}

		delegate:
			CheckBox
			{
				checked:			model.checkState
				text:				model.display
				onCheckedChanged:	model.checkState = checked


				//color:					controlForegroundNeutral
				padding: 			10
			}
	}
}
