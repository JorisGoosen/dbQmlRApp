import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

SplitView
{
	id:				splitView
	orientation:	Qt.Vertical

	FilterList
	{
		title:					"School"
		model:					schoolScannerTable.school
		SplitView.fillHeight:	true
		width:					parent.width
	}
}
