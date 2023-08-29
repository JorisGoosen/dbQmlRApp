import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window
{

	width:		1280
	height:		720
	visible:	true
	color:		windowBackgroundColor



	TabBar
	{
		id:		tabBar

		property bool importerExists:		importer
		property bool schoolScannerExists:	schoolScannerTable

		onImporterExistsChanged:			if(importer)			importer.cellMargin				= Qt.binding(function(){return generalMargin;});
		onSchoolScannerExistsChanged:		if(schoolScannerTable)	schoolScannerTable.cellMargin	= Qt.binding(function(){return generalMargin;});

		Connections
		{
			target:		mainModel
			function	onShowStackIndex(idx) { tabBar.setCurrentIndex(idx); }
		}

		anchors
		{
			top:	parent.top
			left:	parent.left
			right:	parent.right
		}

		Repeater
		{
			model:	mainModel.qmlsShown

			TabButton
			{
				id:		tabButton
				text:	modelData

				property bool selected: index == tabBar.currentIndex

				contentItem:	Text
				{
					color:						tabButton.selected ? controlForegroundFocus : controlForegroundNeutral
					text:						"<b>" + tabButton.text + "</b>"
					font.family:				fontFamilie
					anchors.fill:				parent
					horizontalAlignment:		Text.AlignHCenter
					verticalAlignment:			Text.AlignVCenter
				}

				background: Rectangle
				{
						color:	tabButton.selected ? controlBackgroundFocus : controlBackgroundNeutral
				}
			}
		}
	}

	StackLayout
	{
		id:					stackView
		clip:				true
		onWidthChanged:		R.plotWidth		= width
		onHeightChanged:	R.plotHeight	= height

		currentIndex:		tabBar.currentIndex

		Repeater
		{
			id:		swipeRepeater
			model:	mainModel.qmlsShown

			Loader
			{
				id:				qmlLoader
				source:			modelData + ".qml"
				width:			stackView.width
				height:			stackView.height
			}
		}

		anchors
		{
			top:	tabBar.bottom
			left:	parent.left
			right:	parent.right
			bottom:	parent.bottom
		}
	}

	readonly property Item _toolTipOverrideItem: Item
	{
		//These properties override those for ALL attached ToolTips in the application
		//ToolTip.toolTip shouldn't be changed anywhere else otherwise we get hard to debug behaviour
		ToolTip.toolTip.background:		Rectangle { color: backgroundColor; border.width: 1; border.color: foregroundColor }
		ToolTip.toolTip.contentItem:	Text
		{
			//font:			jaspTheme.font
			wrapMode:		Text.WrapAtWordBoundaryOrAnywhere
			text:			ToolTip.toolTip.text
			font.family:	fontFamilie
		}
		ToolTip.toolTip.z:						1234
	}
}
