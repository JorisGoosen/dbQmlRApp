import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Rectangle
{
    id:						handleMe
    color:					pressed ? controlBackgroundFocus : controlBackgroundNeutral
    border.color:			pressed ? controlForegroundFocus : controlBackgroundNeutral
    border.width:			1
    implicitWidth:			6
	property bool pressed:	false
}
