import QtQuick 


Item
{
	
	property alias rectBack:	rectBack
	Rectangle
	{
		id:					rectBack
		z:					-1
		color:				backgroundColor
		border.color:		foregroundColor
		border.width:		1
		anchors.fill:		parent
		radius:				20
	}
	
	implicitWidth:		tekstWortel.contentWidth	+ 2*generalMargin
	implicitHeight:		tekstWortel.contentHeight	+ 2*generalMargin
	
	property alias text:				tekstWortel.text
	property alias color:				tekstWortel.color
	property alias font:				tekstWortel.font
	property alias horizontalAlignment:	tekstWortel.horizontalAlignment
	property alias verticalAlignment:	tekstWortel.verticalAlignment
	property alias tekstWortel:			tekstWortel

	Text
	{
		id:						tekstWortel
		//font:					"monospace"
		color:					foregroundHColor
		wrapMode:				Text.WrapAtWordBoundaryOrAnywhere
		horizontalAlignment:	Text.AlignHCenter
		verticalAlignment:		Text.AlignVCenter
		textFormat:				Text.RichText
		width:					parent.width
		topPadding:				generalMargin
		leftPadding:			generalMargin
		rightPadding:			generalMargin
		bottomPadding:			generalMargin
		
	}
}
