import QtQuick 
import QtQuick.Controls

Rectangle
{
	id:				pane
	color:			backgroundColor
	
	Flickable
	{
		anchors.fill:	parent
		
		contentHeight:	vals.implicitHeight
		clip:			true;
		
		LastValues
		{
			id:				vals
			width:			pane.width
		}
	}
}

