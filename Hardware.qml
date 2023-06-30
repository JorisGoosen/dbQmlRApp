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

		HWFeedbackButton
		{
			width:			gasFeedback.boxWidth
			height:			gasFeedback.height

			text:			"co2"
			value:			respiro.co2
			checked:		respiro.co2On

			onClicked:		(newChecked)=>{ respiro.co2On = newChecked; }
		}

		HWFeedbackButton
		{
			width:			gasFeedback.boxWidth
			height:			gasFeedback.height

			text:			"ch4"
			value:			respiro.ch4
			checked:		respiro.ch4On

			onClicked:		(newChecked)=>{ respiro.ch4On = newChecked; }
		}

		HWFeedbackButton
		{
			width:			gasFeedback.boxWidth
			height:			gasFeedback.height

			text:			"o2"
			value:			respiro.o2
			checked:		respiro.o2On

			onClicked:		(newChecked)=>{ respiro.o2On = newChecked; }
		}

	}

	//Pump:
	HWFeedbackButton
	{
		id:				pumpBox

		width:			gasFeedback.height
		height:			gasFeedback.boxWidth
		text:			"Pump"
		value:			respiro.pumpOn ? "ON" : "OFF"
		checked:		respiro.pumpOn
		onClicked:		(newChecked)=>{ respiro.pumpOn = newChecked; }

		anchors
		{
			verticalCenter:		backRec.verticalCenter
			horizontalCenter:	backRec.left
		}
	}

	ColumnLayout
	{
		id:		vents

		anchors
		{
			verticalCenter:		backRec.verticalCenter
			horizontalCenter:	backRec.right
		}

		HWFeedbackButton
		{
			id:				vent0Box

			width:			gasFeedback.height
			height:			width + 10
			text:			"Vent Out"
			value:			respiro.vent0 ? "Open" : "Closed"
			checked:		respiro.vent0
			onClicked:		(newChecked)=>{ respiro.vent0 = newChecked; }
		}

		HWFeedbackButton
		{
			id:				vent1Box

			width:			gasFeedback.height
			height:			width + 10
			text:			"Vent In 1"
			value:			respiro.vent1 ? "Open" : "Closed"
			checked:		respiro.vent1
			onClicked:		(newChecked)=>{ respiro.vent1 = newChecked; }
		}

		HWFeedbackButton
		{
			id:				vent2Box

			width:			gasFeedback.height
			height:			width + 10
			text:			"Vent In 2"
			value:			respiro.vent2 ? "Open" : "Closed"
			checked:		respiro.vent2
			onClicked:		(newChecked)=>{ respiro.vent2 = newChecked; }
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

					checked:		respiro.valvesOpened[index]
					onClicked:		(newChecked)=>{ respiro.push_valve_state(index, newChecked); }

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

					checked:		respiro.valvesOpened[index]
					onClicked:		(newChecked)=>{ respiro.push_valve_state(index, newChecked); }

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
			text:				"<b>Temperature1:</b>&nbsp;" + respiro.temp1 + "<sup>c</sup><br><b>Temperature2:</b>&nbsp;" + respiro.temp2 + "<sup>c</sup><br><b>Pressure:</b>&nbsp;" + respiro.pressure + "bar"
			anchors.centerIn:	parent
			color:				foregroundColor
		}
	}
}
