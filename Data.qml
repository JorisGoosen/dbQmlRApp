import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


MySplitView
{
	orientation:			Qt.Vertical
	SplitView.fillWidth:	true

	Tafel
	{
		model:						respiroDataProc

		columnWidthProvider:		respiroDataProc.columnWidthProvider
		rowHeightProvider:			respiroDataProc.rowHeightProvider
		
		SplitView.preferredHeight: parent.height * 0.5

		//visible:					respiroDataProc.rowCount > 0
	}

	Tafel
	{
		model:						respiroDataMeas

		columnWidthProvider:		respiroDataMeas.columnWidthProvider
		rowHeightProvider:			respiroDataMeas.rowHeightProvider
		//SplitView.fillHeight:		true
		SplitView.preferredHeight: parent.height * 0.5
		//visible:					respiroDataMeas.rowCount > 0
	}

	//Image
	//{
	//	source: "dummy.png"
	//	SplitView.preferredHeight: parent.height * 0.666667

	//	onWidthChanged:			R.plotWidth		= width
	//	onHeightChanged:		R.plotHeight	= height
	//}

	//Tafel
	//{
	//	model:						respiroMsgs

	//	columnWidthProvider:		respiroMsgs.columnWidthProvider
	//	rowHeightProvider:			respiroMsgs.rowHeightProvider

	//	SplitView.minimumHeight:	model.rowCount > 0 ? 200 : 0
	//	SplitView.preferredHeight:	parent.height * 0.333333
	//	//visible:					respiroMsgs.rowCount > 0
	//}
		
	LastValues
	{
		implicitWidth:			parent.width
		
		SplitView.preferredHeight:	implicitHeight
		SplitView.minimumHeight:	implicitHeight
		SplitView.maximumHeight:	implicitHeight
		
	}
}

