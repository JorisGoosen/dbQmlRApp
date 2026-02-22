import QtQuick 

Text
{
	id:						tekstWortel
	font:					"monospace"
	color:					foregroundHColor
	wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
	horizontalAlignment:	Text.AlignHCenter
	verticalAlignment:		Text.AlignVCenter
	
	
	topPadding:				generalMargin
	leftPadding:			generalMargin
	rightPadding:			generalMargin
	bottomPadding:			generalMargin
	
	Rectangle
	{
		z:					-1
		color:				backgroundColor
		border.color:		foregroundColor
		border.width:		1
		anchors.fill:		tekstWortel
	}
}
