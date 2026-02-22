import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item
{
	ColumnLayout
	{
		id:					columnLayout
		height:				parent.height
		spacing:			generalMargin
		width:				parent.width * .5
		anchors.centerIn:	parent
		
		Item
		{
			Layout.fillHeight: true	
		}
		
		Repeater
		{
			model:	respiro.feedback
	
			Rectangle
			{
				border.color:	feedbackStatus.color
				border.width:	1
	
				width:			columnLayout.width
				height:			30
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
		
		Item
		{
			Layout.fillHeight: true	
		}
	}
}
