import QtQuick 

Item 
{
	property string channelId:	"???";
	
	width:				implicitWidth
	height:				implicitHeight
	
	implicitWidth:		120
	implicitHeight:		120
	
	Rectangle
	{	
		radius:				200
		anchors.fill:		parent
		
		
		MyText
		{
			text:				channelId
			anchors.centerIn:	parent
		}
		
	}
	
}
