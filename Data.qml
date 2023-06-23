import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

SplitView
{
	orientation:	Qt.Horizontal

	Tafel
	{
		model:						respiroData

		columnWidthProvider:		respiroData.columnWidthProvider
		rowHeightProvider:			respiroData.rowHeightProvider

		SplitView.preferredWidth:	parent.width * 0.33333
	}

	SplitView
	{
		orientation: Qt.Vertical

		SplitView.preferredWidth: parent.width * 0.666667

		Image
		{
			source: "dummy.png"
			SplitView.preferredHeight: parent.height * 0.666667
		}

		Tafel
		{
			model:						respiroMsgs

			columnWidthProvider:		respiroMsgs.columnWidthProvider
			rowHeightProvider:			respiroMsgs.rowHeightProvider

			SplitView.minimumHeight:	model.rowCount > 0 ? 200 : 0
			SplitView.preferredHeight:	parent.height * 0.333333
		}
	}
}
