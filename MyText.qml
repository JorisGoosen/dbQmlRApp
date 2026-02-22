import QtQuick 


Item
{
	
	
	Rectangle
	{
		z:					-1
		color:				backgroundColor
		border.color:		foregroundColor
		border.width:		1
		anchors.fill:		parent
		radius:				20
	}
	
	implicitWidth:		tekstWortel.implicitWidth
	implicitHeight:		tekstWortel.implicitHeight
	
	property alias text:				tekstWortel.text
	property alias color:				tekstWortel.color
	property alias font:				tekstWortel.font
	property alias horizontalAlignment:	tekstWortel.horizontalAlignment
	property alias verticalAlignment:	tekstWortel.verticalAlignment

	Text
	{
		id:						tekstWortel
		font:					"monospace"
		color:					foregroundHColor
		wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
		horizontalAlignment:	Text.AlignHCenter
		verticalAlignment:		Text.AlignVCenter
		textFormat:				Text.RichText
		
		topPadding:				generalMargin
		leftPadding:			generalMargin
		rightPadding:			generalMargin
		bottomPadding:			generalMargin
		
	}
}
