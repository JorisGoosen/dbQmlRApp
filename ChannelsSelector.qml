import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Item
{
	id: rootHere
	property alias model:	channelRepeater.model

	height:	scroller.height

	ScrollView
	{
		id:						scroller
		anchors
		{
			horizontalCenter:	parent.horizontalCenter
		}

		width:				Math.min(titleAndMore.implicitWidth, rootHere.width)
		height:				titleAndMore.height

		Rectangle
		{
			id:				titleAndMore
			implicitWidth:	rowLayout.width
			implicitHeight:	rowLayout.y + rowLayout.height + generalMargin

			color:			controlBackgroundNeutral
			border.color:	controlForegroundNeutral
			border.width:	1

			Text
			{
				id:						titleText
				text:					"<b>Select channels</b>"
				color:					controlForegroundNeutral
				wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
				horizontalAlignment:	Text.AlignHCenter
				verticalAlignment:		Text.AlignVCenter
				x:						scroller.width / 2
				y:						generalMargin
			}


			RowLayout
			{
				id:		rowLayout

				anchors
				{
					top:	titleText.bottom
					left:	parent.left
				}

				Repeater
				{
					id:		channelRepeater

					CheckBox
					{
						text:				index
						checked:			modelData
						onCheckedChanged:	if(checked != modelData) respiro.setChannelInit(index, checked);
					}
				}

			}
		}
	}
}
