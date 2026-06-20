import QtQuick 
import QtQuick.Layouts

Rectangle
{
	color:			"purple"
	
	RowLayout
	{
		anchors.fill:		parent
		anchors.margins:	generalMargin
		
		Repeater 
		{
			model:		respiro
			
			ChannelStatus
			{
				channelId:		modelData	
			}
		}
	}
}
