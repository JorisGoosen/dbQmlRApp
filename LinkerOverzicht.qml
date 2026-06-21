import QtQuick 
import QtQuick.Layouts
import QtQuick.Controls

Rectangle
{
	id:				pane
	color:			backgroundColor
	
	ColumnLayout
	{
		id:			dbCol
		
		Text
		{
			text:			"<b>DB:"
			color:			foregroundColor
			width:	parent.width; leftPadding:	2; rightPadding: 2;
		}
		
		TextArea
		{
			text:			respiro.dbPath
			font:			"monospace"
			color:			foregroundColor
			width:			parent.width
			wrapMode:		Text.WrapAtWordBoundaryOrAnywhere
			readOnly:		true
			selectByMouse:	true	
			leftPadding:	2; 
			rightPadding:	2;
		}
		
		anchors
		{
			top:			parent.top
			left:			parent.left
			right:			parent.right
		}
	}
	
	ScrollView
	{
		anchors
		{
			top:			dbCol.bottom
			left:			parent.left
			right:			parent.right
			bottom:			parent.bottom
		}
		contentHeight:	vals.implicitHeight
		contentWidth:	pane.width
		clip:			true;
		
		LastValues
		{
			id:				vals
			width:			pane.width
		}
	}
}

