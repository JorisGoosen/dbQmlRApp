import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item
{
	id:		hardwareRoot

	anchors
	{
		fill: parent
	}

	//Big black background rectangle:
	Rectangle
	{
		id:				backRec
		color:			backgroundColor
		border.color:	foregroundColor
		border.width:	1
		z:				-1

		anchors
		{
			margins:	100
			fill:		parent
		}
	}

	//Toprow with gas feedback and buttons
	RowLayout
	{
		id:		gasFeedback
		height: 75

		property int boxWidth:		height * 2
		property int widthRemain:	backRec.width - (boxWidth * 3)

		//spacing:	widthRemain / 4

		anchors
		{
			verticalCenter:	backRec.top
			left:			backRec.left
			right:			backRec.right
			leftMargin:		widthRemain / 4
		}

		Repeater
		{

			model:	["co2", "ch4", "o2"]

			HWFeedbackButton
			{
				width:			gasFeedback.boxWidth
				height:			gasFeedback.height

				text:			modelData
				value:			1234
			}
		}
	}

	//Pump:
	HWFeedbackButton
	{
		id:				pumpBox

		width:			gasFeedback.height
		height:			gasFeedback.boxWidth
		text:			"Pump"
		value:			"ON"

		anchors
		{
			verticalCenter:		backRec.verticalCenter
			horizontalCenter:	backRec.left
		}
	}

	//The actual channel buttons:
	RowLayout
	{
		id:		channelsRow

		anchors
		{
			verticalCenter:	backRec.bottom
			left:			backRec.left
			right:			backRec.right
			leftMargin:		generalMargin
		}

		Rectangle
		{
			color:			backgroundColor
			border.color:	foregroundColor
			border.width:	1
			width:			channelsText.contentWidth	+ generalMargin
			height:			channelsText.contentHeight	+ generalMargin

			Text
			{
				id:					channelsText
				color:				foregroundColor
				text:				"<b>Channels:</b> "
				anchors.centerIn:	parent
			}
		}

		property int channelButtonsHeight: 150

		Repeater
		{
			id:		channelsRepeater
			model:	13

			Item
			{
				id:		channelButtonsItem
				height: channelsRow.channelButtonsHeight
				width:	50

				ChannelButton
				{
					id:				inButton
					width:			channelButtonsItem.width

					anchors
					{
						top:				channelButtonsItem.top
						horizontalCenter:	channelButtonsItem.horizontalCenter
					}
				}

				Rectangle
				{
					color:	foregroundColor
					width:	inButton.border.width
					z:		-1

					anchors
					{
						horizontalCenter:	inButton.horizontalCenter
						top:				inButton.verticalCenter
						bottom:				outButton.verticalCenter
					}

					Rectangle
					{
						width:			channelNumberText.contentWidth	+ 10
						height:			channelNumberText.contentHeight	+ 10
						color:			backgroundColor
						border.color:	foregroundColor
						border.width:	1

						Text
						{
							id:					channelNumberText
							color:				foregroundColor
							text:				"<b>" + (index) + "</b>"
							anchors.centerIn:	parent
						}

						anchors.centerIn:		parent
					}
				}

				ChannelButton
				{
					id:				outButton
					width:			channelButtonsItem.width

					anchors
					{
						bottom:				channelButtonsItem.bottom
						horizontalCenter:	channelButtonsItem.horizontalCenter
					}
				}
			}
		}

		Item
		{
			id:		channelButtonsInOutItem
			height: channelsRow.channelButtonsHeight
			width:	50

			Rectangle
			{
				id:				channelInTextBox
				width:			channelButtonsInOutItem.width
				height:			channelButtonsInOutItem.width
				color:			backgroundColor
				border.color:	foregroundColor
				border.width:	1

				Text
				{
					id:					channelInText
					color:				foregroundColor
					text:				"<b>In</b>"
					anchors.centerIn:	parent
				}

				anchors
				{
					top:				channelButtonsInOutItem.top
					horizontalCenter:	channelButtonsInOutItem.horizontalCenter
				}
			}

			Rectangle
			{
				id:				channelOutTextBox
				width:			channelButtonsInOutItem.width
				height:			channelButtonsInOutItem.width
				color:			backgroundColor
				border.color:	foregroundColor
				border.width:	1

				Text
				{
					id:					channelOutText
					color:				foregroundColor
					text:				"<b>Out</b>"
					anchors.centerIn:	parent
				}

				anchors
				{
					bottom:				channelButtonsInOutItem.bottom
					horizontalCenter:	channelButtonsInOutItem.horizontalCenter
				}
			}
		}

	}

	//Temp and pressure box
	Rectangle
	{
		id:					temperaturePressureBox
		color:				backgroundColor
		border.color:		foregroundColor
		border.width:		1
		anchors.centerIn:	backRec
		width:				temperaturePressureText.contentWidth  + generalMargin
		height:				temperaturePressureText.contentHeight + generalMargin

		Text
		{
			id:					temperaturePressureText
			text:				"<b>Temperature:</b>&nbsp;12<sup>c</sup><br><b>Pressure:</b>&nbsp;1bar"
			anchors.centerIn:	parent
			color:				foregroundColor
		}
	}
}
