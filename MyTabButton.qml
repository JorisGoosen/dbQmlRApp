import QtQuick
import QtQuick.Controls

TabButton
{
	id:		tabButton

	property bool selected: false

	contentItem:	Text
	{
		color:						muisje.containsMouse || tabButton.selected ? controlForegroundFocus : controlForegroundNeutral
		text:						"<b>" + tabButton.text + "</b>"
		font.family:				fontFamilie
		anchors.fill:				parent
		horizontalAlignment:		Text.AlignHCenter
		verticalAlignment:			Text.AlignVCenter
	}

	background:
		Item {
			   Rectangle
			   {
					  color:				muisje.containsMouse ||tabButton.selected ? controlBackgroundFocus : controlBackgroundNeutral
					   border.color:		muisje.containsMouse ||tabButton.selected ? controlForegroundFocus : controlBackgroundNeutral
					   border.width:		1
					   anchors.fill:		parent
					   anchors.margins:		dikkeLijnDikte / 2
			   }
		   }


	MouseArea
	{
		id:					muisje
		acceptedButtons:	Qt.NoButton
		hoverEnabled:		true
		anchors.fill:		parent
		cursorShape:		Qt.PointingHandCursor
		z:					1000
	}

}
