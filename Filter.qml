import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

SplitView
{
	id:				splitView
	orientation:	Qt.Vertical

	property var fillThisOne:	schoolScannerTable.school

	FilterList	{ model:	schoolScannerTable.school	}
	FilterList	{ model:	schoolScannerTable.locatie 	}
	FilterList	{ model:	schoolScannerTable.sector 	}
	FilterList	{ model:	schoolScannerTable.niveau 	}
	FilterList	{ model:	schoolScannerTable.leerjaar }
	FilterList	{ model:	schoolScannerTable.klas 	}
	FilterList	{ model:	schoolScannerTable.gender 	}
	FilterList	{ model:	schoolScannerTable.cultuur 	}
}
