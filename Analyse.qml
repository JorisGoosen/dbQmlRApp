import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

SplitView
{
	id:				splitView
	orientation:	Qt.Horizontal

	Filter
	{
		SplitView.preferredWidth:	splitView.width / 2
	}

	Plots
	{

	}
}
