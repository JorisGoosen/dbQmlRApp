import QtQuick 
import QtQuick.Layouts

Rectangle
{
	color:			backgroundColor
	
	Item
	{
		id:					leftItem
		anchors
		{
			top:			parent.top
			left:			parent.left
			bottom:			parent.bottom
		}
		
		width:				Math.max(0, (parent.width - (2*generalMargin + theList.contentWidth)) / 2)
	}
	
	ListView
	{
		id:					theList
		
		anchors
		{
			top:			parent.top
			left:			leftItem.right
			right:			rightItem.left
			bottom:			parent.bottom
			margins:		generalMargin
		}
		
		orientation:		Qt.Horizontal
		model:				respiro
		delegate:			ChannelStatus { }
	}
	
	Item
	{
		id:					rightItem
		anchors
		{
			top:			parent.top
			right:			parent.right
			bottom:			parent.bottom
		}
		width:				leftItem.width
	}
}
