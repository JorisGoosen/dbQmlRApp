import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle
{
	id: rootHere
	property alias model:	channelRepeater.model

	height:	scroller.height
	
	color:			controlBackgroundNeutral
	border.color:	controlForegroundNeutral
	border.width:	1

	ScrollView
	{
		id:						scroller
		anchors
		{
			horizontalCenter:	parent.horizontalCenter
		}

		width:				parent.width
		height:				titleAndMore.height

		Item
		{
			id:				titleAndMore
			implicitWidth:	rowLayout.width
			implicitHeight:	rowLayout.y + rowLayout.height + 2*generalMargin


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
}
