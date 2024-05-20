import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Rectangle
{
    id:						handleMe
    color:					SplitHandle.pressed ? controlBackgroundFocus : controlBackgroundNeutral
    border.color:			SplitHandle.pressed ? controlForegroundFocus : controlBackgroundNeutral
    border.width:			1
    implicitWidth:			6
}