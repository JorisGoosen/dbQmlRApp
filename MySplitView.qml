import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


SplitView
{
	id:						splitView
	
	handle: Rectangle 
	{
		id:					handleDelegate
		implicitWidth:		4
		implicitHeight:		4
		color:				SplitHandle.pressed 
								? "#000000"
								: SplitHandle.hovered 
								  ? "#cccccc" 
								  : "#ffffff"
	}
}
