import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle
{
	id: rootHere
	property alias model:	channelRepeater.model

	height:			titleAndMore.height
	
	color:			controlBackgroundNeutral
	border.color:	controlForegroundNeutral
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
			color:						controlForegroundNeutral
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

				CheckBox
				{
					text:				index + 1
					checked:			modelData
					onCheckedChanged:	if(checked != modelData) respiro.setChannelInit(index, checked);
				}
			}

		}
	}
}
