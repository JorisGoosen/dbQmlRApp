import QtQuick 2.15

Rectangle
{
	property bool	checked:	true

	color:			checked ? "green" : "red"
	border.color:	foregroundColor
	border.width:	4
	radius:			width
	height:			width

	signal clicked(bool newChecked);

	MouseArea
	{
		anchors.fill: parent
		onClicked:	parent.clicked(!checked)
	}
}
