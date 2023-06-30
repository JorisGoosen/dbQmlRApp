import QtQuick 2.15


Rectangle
{
	property string text:		""
	property string	value:		""
	property bool	horizontal:	width >= height
	property alias	checked:	button.checked

	id:				feedbackRoot
	color:			backgroundColor
	border.color:	foregroundColor
	border.width:	1

	signal clicked(bool newChecked);

	ChannelButton
	{
		id:			button
		width:		40

		onClicked: (newChecked)=>{ parent.clicked(newChecked); }

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
		wrapMode:			Text.WrapAtWordBoundaryOrAnywhere
	}
}
