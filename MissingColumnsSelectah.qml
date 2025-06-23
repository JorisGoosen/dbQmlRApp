import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FocusScope
{
	visible:	importer && importer.canImport && columnsList.count > 0
	implicitWidth:		parent.width
	implicitHeight:		Math.min(columnsList.contentHeight, parent.height / 2)

	height:	implicitHeight
	width: implicitWidth
	ListView
	{
		id:				columnsList
		model:			importer.ignoredCols
		anchors.fill:	parent

		delegate: Rectangle
		{
			implicitHeight:	rij.height
			implicitWidth:	rij.width

			color:				controlBackgroundNeutral

			Row
			{
				id:		rij

				Text
				{
					text:					modelData
					width:					(columnsList.width/4)*2
					font.bold:				true
					font.family:			fontFamilie
					font.pixelSize:			14
					color:					controlForegroundNeutral
					horizontalAlignment:	Text.AlignHCenter
					verticalAlignment:		Text.AlignVCenter
					height:					toevoeger.height
					visible:				!control.down
				}

				ComboBox
				{
					id:						control
					width:					!down ? (columnsList.width/4) : columnsList.width
					model:					importer.columnTitles
					font.bold:				true
					font.family:			fontFamilie
					font.pixelSize:			14
					height:					toevoeger.height

					MouseArea
					{
						id:					comboMuis
						anchors.fill:		parent
						acceptedButtons:	Qt.NoButton
						hoverEnabled:		 true
					}

					background: Rectangle
					{
						color:				!comboMuis.containsMouse ? controlBackgroundNeutral : controlBackgroundFocus
						border.width:		1
						border.color:		!comboMuis.containsMouse ? controlForegroundNeutral : controlForegroundFocus
					}

					contentItem: Text
					{
						text:					control.displayText
						color:					!comboMuis.containsMouse ? controlForegroundNeutral : controlForegroundFocus
						font.bold:				true
						font.family:			fontFamilie
						font.pixelSize:			14
						horizontalAlignment:	Text.AlignHCenter
						verticalAlignment:		Text.AlignVCenter
					}

					delegate: ItemDelegate
					{
						id: delegate

						required property var model
						required property int index

						implicitWidth:		control.width

						contentItem: Text
						{
							text:					delegate.model[control.textRole]
							color:					controlForegroundNeutral
							font.bold:				true
							font.family:			fontFamilie
							font.pixelSize:			14
							horizontalAlignment:	Text.AlignHCenter
							verticalAlignment:		Text.AlignVCenter
						}
						background: Rectangle
						{
							color:				controlBackgroundNeutral
							border.width:		1
							border.color:		controlForegroundNeutral
						}
						highlighted: control.highlightedIndex === index
					}
				}

				RectButton
				{
					id:			toevoeger
					width:		columnsList.width/4
					text:		"Voeg toe"
					groot:		false
					visible:	!control.down
					onClicked:	{
						importer.addCustomCsvToDb(modelData, control.displayText);
					}
				}
			}
		}
	}

}
