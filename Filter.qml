import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Flickable
{
	id:					flickDieSplit
	contentHeight:		splitView.height

	SplitView
	{
		id:						splitView
		orientation:			Qt.Vertical
		visible:				schoolScannerTable
		height:					Math.max(800, flickDieSplit.height)
		width:					flickDieSplit.width
		enabled:				!plotList.renderMaar
		opacity:				enabled ? 1.0 : 0.5

		property var fillThisOne:	schoolScannerTable.school

		handle:	Rectangle
		{
			color:			SplitHandle.hovered ? controlForegroundFocus : controlForegroundNeutral
			implicitWidth:	6
			implicitHeight:	6
		}

		FilterList	{ model:	!schoolScannerTable ? null : schoolScannerTable.school		}
		FilterList	{ model:	!schoolScannerTable ? null : schoolScannerTable.locatie 	}
		FilterList	{ model:	!schoolScannerTable ? null : schoolScannerTable.sector	 	}
		FilterList	{ model:	!schoolScannerTable ? null : schoolScannerTable.niveau	 	}
		FilterList	{ model:	!schoolScannerTable ? null : schoolScannerTable.leerjaar	}
		FilterList	{ model:	!schoolScannerTable ? null : schoolScannerTable.klas		}
		FilterList	{ model:	!schoolScannerTable ? null : schoolScannerTable.gender		}
		FilterList	{ model:	!schoolScannerTable ? null : schoolScannerTable.cultuur 	}
		FilterList	{ model:	!schoolScannerTable ? null : schoolScannerTable.type	 	}
	}

	ScrollBar.vertical:		Scrollbalk { visible: splitView.height != flickDieSplit.height}
}
