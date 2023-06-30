import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

SplitView
{
	orientation:	Qt.Horizontal

	SplitView
	{
		orientation: Qt.Vertical
		SplitView.preferredWidth:	parent.width * 0.33333

		Tafel
		{
			model:						respiroDataProc

			columnWidthProvider:		respiroDataProc.columnWidthProvider
			rowHeightProvider:			respiroDataProc.rowHeightProvider

			//visible:					respiroDataProc.rowCount > 0
		}

		Tafel
		{
			model:						respiroDataMeas

			columnWidthProvider:		respiroDataMeas.columnWidthProvider
			rowHeightProvider:			respiroDataMeas.rowHeightProvider

			//visible:					respiroDataMeas.rowCount > 0
		}
	}

	SplitView
	{
		orientation: Qt.Vertical

		SplitView.preferredWidth: parent.width * 0.666667

		Image
		{
			source: "dummy.png"
			SplitView.preferredHeight: parent.height * 0.666667

			onWidthChanged:			R.plotWidth		= width
			onHeightChanged:		R.plotHeight	= height
		}

		Tafel
		{
			model:						respiroMsgs

			columnWidthProvider:		respiroMsgs.columnWidthProvider
			rowHeightProvider:			respiroMsgs.rowHeightProvider

			SplitView.minimumHeight:	model.rowCount > 0 ? 200 : 0
			SplitView.preferredHeight:	parent.height * 0.333333
			//visible:					respiroMsgs.rowCount > 0
		}
	}
}
