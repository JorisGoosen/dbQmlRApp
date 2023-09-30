import QtQuick
import QtQuick.Controls

Rectangle
{
	id:	buttonRoot

	signal clicked();

	property alias text:		buttonText.text
	property string toolTip:	""
	property int margins:		groot ? generalMargin : generalMargin / 2
	property bool groot:		true

	implicitWidth:	buttonText.contentWidth  + margins * 2
	implicitHeight:	buttonText.contentHeight + margins * 2

	color:			!enabled ? controlBackgroundDisabled : buttonMouseArea.pressed ? controlBackgroundPressed : buttonMouseArea.containsMouse ? controlBackgroundFocus : controlBackgroundNeutral
	border.color:	!enabled ? controlForegroundDisabled : buttonMouseArea.pressed ? controlForegroundPressed : buttonMouseArea.containsMouse ? controlForegroundFocus : controlForegroundNeutral
	border.width:	2

	Text
	{
		id:						buttonText
		color:					buttonRoot.border.color
		anchors.fill:			parent
		anchors.margins:		buttonRoot.margins
		font.bold:				true
		font.family:			fontFamilie
		font.pixelSize:			groot ? 25 : 14
		horizontalAlignment:	Text.AlignHCenter
		verticalAlignment:		Text.AlignVCenter
	}

	ToolTip.text:		toolTip
	ToolTip.timeout:	10000
	ToolTip.delay:		500
	ToolTip.visible:	toolTip !== "" && buttonMouseArea.containsMouse

	MouseArea
	{
		id:				buttonMouseArea
		anchors.fill:	parent
		onPressed:		buttonRoot.clicked()
		hoverEnabled:	true
		cursorShape:	Qt.PointingHandCursor
	}
}
