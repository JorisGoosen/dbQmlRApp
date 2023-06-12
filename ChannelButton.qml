import QtQuick 2.15

Rectangle
{
	property bool mockMe:	true
	color:			mockMe ? "green" : "red"
	border.color:	foregroundColor
	border.width:	4
	radius:			width
	height:			width

	MouseArea
	{
		anchors.fill: parent
		onClicked:	parent.mockMe = !parent.mockMe
	}
}
