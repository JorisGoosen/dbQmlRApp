import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

SplitView
{
	id:				splitView
	orientation:	Qt.Vertical
	visible:		schoolScannerTable

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
