import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout
{
	id:			columnLayout
	Repeater
	{
		model:	respiro.feedback

		Rectangle
		{
			border.color:	feedbackStatus.color
			border.width:	1

			width:			childrenRect.width		+ 20
			height:			childrenRect.height		+ 20
			radius:			height

			Layout.alignment: Qt.AlignHCenter

			Item
			{
				anchors.centerIn:	parent
				width:				Math.max(Math.max(feedbackMsg.contentWidth, feedbackErrorMsg.contentWidth)*2 + feedbackStatus.width, columnLayout.width / 2)
				height:				feedbackMsg.height

				Text
				{
					id:		feedbackMsg
					text:	modelData

					anchors
					{
						right:			feedbackStatus.left
						rightMargin:		10
						verticalCenter:	parent.verticalCenter
					}

				}

				Rectangle
				{
					id:		feedbackStatus
					radius:	width
					height:	feedbackMsg.height
					width:	height
					color:	!respiro.feedbackFinished(modelData) ? "blue" : !respiro.feedbackError(modelData) ? "green" : "red"

					anchors.centerIn: parent
				}

				Text
				{
					id:		feedbackErrorMsg
					text:	respiro.feedbackError(modelData)
					color:	"darkred"

					anchors
					{
						left:			feedbackStatus.right
						leftMargin:		10
						verticalCenter:	parent.verticalCenter
					}
				}
			}
		}
	}
}
