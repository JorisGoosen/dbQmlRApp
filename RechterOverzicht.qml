import QtQuick 
import QtQuick.Layouts
import QtQuick.Controls


Rectangle
{
	id:				pane
	color:			backgroundColor
	
	ScrollView
	{
		anchors.fill:	parent

		ColumnLayout 
		{
			width:					pane.width
			clip:					true
			
			RectButton
			{
				text:				"Rerun leaktests"
				onClicked:			respiro.leakTests();
				enabled:			!respiro.running
				implicitWidth:		parent.width
			}
			
			RectButton
			{
				text:				"Start measurements"
				onClicked:			!respiro.controlWanted && respiro.startMeasuring();
				enabled:			!respiro.running
				implicitWidth:		parent.width
			}
			
			MyCheckbox
			{
				checked:			respiro.controlWanted
				onCheckedChanged:	respiro.controlWanted = checked
				text:				"Manual Control"
				implicitWidth:		parent.width
			}
			
			MyCheckbox
			{
				checked:			respiro.pumpOn
				onCheckedChanged:	respiro.pumpOn = checked
				text:				"Pump On"
				enabled:			respiro.controlWanted && !respiro.running
				implicitWidth:		parent.width
			}
			
			MyCheckbox
			{
				checked:			respiro.vent0
				onCheckedChanged:	respiro.vent0 = checked
				text:				"Vent OUT"
				enabled:			respiro.controlWanted && !respiro.running
				implicitWidth:		parent.width
			}
			
			MyCheckbox
			{
				checked:			respiro.vent1
				onCheckedChanged:	respiro.vent1 = checked
				text:				"Vent 1"
				enabled:			respiro.controlWanted && !respiro.running
				implicitWidth:		parent.width
			}
			
			MyCheckbox
			{
				checked:			respiro.vent2
				onCheckedChanged:	respiro.vent2 = checked
				text:				"Vent 2"
				enabled:			respiro.controlWanted && !respiro.running
				implicitWidth:		parent.width
			}
			
			RectButton
			{
				text:				"Basal State 1"
				onClicked:			respiro.basalState(1)
				enabled:			respiro.controlWanted && !respiro.running
				implicitWidth:		parent.width
			}
			
			RectButton
			{
				text:				"Basal State 2"
				onClicked:			respiro.basalState(2)
				enabled:			respiro.controlWanted && !respiro.running
				implicitWidth:		parent.width
			}
			
			RectButton
			{
				text:				"Basal State 99"
				onClicked:			respiro.basalState(99)
				enabled:			respiro.controlWanted && !respiro.running
				implicitWidth:		parent.width
			}
			
			Item
			{
				Layout.fillHeight:	true	
			}
		}
	}
}
