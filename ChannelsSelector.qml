import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle
{
	id: rootHere
	property alias model:	channelRepeater.model

	height:			titleAndMore.height
	
	color:				"#222222"
	border.color:		controlBackgroundNeutral
	border.width:	1


	Item
	{
		id:				titleAndMore
		implicitWidth:	rowLayout.width
		implicitHeight:	rowLayout.y + rowLayout.height + 2*generalMargin
		
		anchors
		{
			top:				parent.top
			topMargin:			generalMargin
			horizontalCenter:	parent.horizontalCenter
		}


		Text
		{
			id:							titleText
			text:						"<b>Select channels</b>"
			color:						controlBackgroundNeutral
			wrapMode:					Text.WrapAtWordBoundaryOrAnywhere
			horizontalAlignment:		Text.AlignHCenter
			verticalAlignment:			Text.AlignVCenter
			anchors.horizontalCenter:	parent.horizontalCenter
		}


		RowLayout
		{
			id:		rowLayout

			anchors
			{
				top:				titleText.bottom
				horizontalCenter:	parent.horizontalCenter
			}

			Repeater
			{
				id:		channelRepeater

				MyCheckbox
				{
					text:				index
					checked:			modelData
					onCheckedChanged:	if(checked != modelData) respiro.setChannelInit(index, checked);
				}
			}

		}
	}
}
