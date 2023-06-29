import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item
{
	id:						column
	property alias title:	titleText.text
	property alias model:	list.model

	Text
	{
		id:						titleText
		color:					controlForegroundNeutral
		wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
		horizontalAlignment:	Text.AlignHCenter
		verticalAlignment:		Text.AlignVCenter
		padding: 				generalMargin

		anchors
		{
			horizontalCenter:	parent.horizontalCenter
		}
	}

	ListView
	{
		id:						list
		clip:					true

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
				padding: 				generalMargin
			}
	}
}
