import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

SplitView
{
	id:				splitView
	orientation:	Qt.Horizontal

	handle: Rectangle
		{
			color:			SplitHandle.hovered ? controlForegroundFocus : controlForegroundNeutral
			implicitWidth:	dikkeLijnDikte
			implicitHeight:	dikkeLijnDikte
		}

	Filter
	{
		SplitView.preferredWidth:	splitView.width / 2
	}

	Plots
	{
		visible:			plotList.showMe
	}

	Item
	{
		visible:					!plotList.renderMaar
		RectButton
		{
			text:					"Maak & toon grafieken"
			onClicked:				plotList.renderMaarIets()
			anchors.centerIn:		parent
			margins:				parent.width / 8
		}
	}
}
