import QtQuick 2.15


Rectangle
{
	property string text:		""
	property var	value:		""
	property bool	horizontal:	width > height

	id:				feedbackRoot
	color:			backgroundColor
	border.color:	foregroundColor
	border.width:	1

	ChannelButton
	{
		width:		40
		anchors
		{
			margins:			5

			verticalCenter:		 feedbackRoot.horizontal ? parent.verticalCenter	: undefined
			left:				 feedbackRoot.horizontal ? parent.left				: undefined

			horizontalCenter:	!feedbackRoot.horizontal ? parent.horizontalCenter	: undefined
			top:				!feedbackRoot.horizontal ? parent.top				: undefined
		}
	}

	Text
	{
		id:					feedbackText
		color:				foregroundColor
		text:				"<b>" + feedbackRoot.text + ":</b><br>" + feedbackRoot.value
		anchors.centerIn:	parent
	}
}
