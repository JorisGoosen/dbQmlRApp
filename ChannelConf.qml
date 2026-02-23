import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtCore


ScrollView
{
	ColumnLayout
	{
		Repeater
		{
			//Channelsconfs hier?
			model:			respiro.channelConfs
			delegate:		channelConfComp
		}
		
		RectButton
		{
			text:				"Start"
			onClicked:			respiro.start();
			Layout.alignment:	Qt.AlignHCenter
		}
	}
	
	Component
	{
		id:		channelConfComp
		
		Rectangle
		{
			
			required property var modelData;
			
			property int localTextFieldWidth: 150
			
			Layout.alignment:	Qt.AlignHCenter
			
			color:			backgroundHColor
			border.color:	foregroundHColor
			border.width:	1
			
			width:			rijtje.implicitWidth  + 2 * generalMargin //generalMargin*2 + Math.max(regel1.implicitWidth, regel2.implicitWidth)
			height:			rijtje.implicitHeight + 2 * generalMargin  //regel2.y + regel2.height + 2*generalMargin
			
			GridLayout
			{
				id:					rijtje
				anchors.centerIn:	parent
				columns:			4
			
			
				MyText
				{
					text:			"Channel #" + modelData.channelID
					implicitWidth:	200
				}
				
				RowLayout
				{
					Text
					{
						text:	"SampleID: "
						color:	foregroundHColor
						Layout.preferredWidth:		localTextFieldWidth
						
					}	
					
					TextField
					{
						text:			modelData.sampleID
						onTextChanged:	modelData.sampleID = text
					}
				}
				
				RowLayout
				{
					Text
					{
						text:	"hsVol_ml: "
						color:	foregroundHColor
						Layout.preferredWidth:		localTextFieldWidth
					}	
					
					TextField
					{
						text:			modelData.hsVol_ml
						onTextChanged:	modelData.hsVol_ml = text
						validator:		DoubleValidator {}
					}
				}
				
				
				RowLayout
				{
					Text
					{
						text:	"CO2max_ppm: "
						color:	foregroundHColor
						Layout.preferredWidth:		localTextFieldWidth
					}	
					
					TextField
					{
						text:			modelData.CO2max_ppm
						onTextChanged:	modelData.CO2max_ppm = text
						validator:		DoubleValidator {}
						
					}
				}
				
				Item{}

				RowLayout
				{
					Text
					{
						text:	"CH4max_ppm: "
						color:	foregroundHColor
						Layout.preferredWidth:		localTextFieldWidth
					}	
					
					TextField
					{
						text:			modelData.CH4max_ppm
						onTextChanged:	modelData.CH4max_ppm = text
						validator:		DoubleValidator {}
					}
				}
				
				RowLayout
				{
					Text
					{
						text:	"O2min_perc: "
						color:	foregroundHColor
						Layout.preferredWidth:		localTextFieldWidth
					}	
					
					TextField
					{
						text:			modelData.O2min_perc
						onTextChanged:	modelData.O2min_perc = text
						validator:		DoubleValidator {}
					}
				}
				
				RowLayout
				{
					Text
					{
						text:	"O2max_perc: "
						color:	foregroundHColor
						Layout.preferredWidth:		localTextFieldWidth
					}	
					
					TextField
					{
						text:			modelData.O2max_perc
						onTextChanged:	modelData.O2max_perc = text
						validator:		DoubleValidator {}
					}
				}			
			
			}
		}
	}
}
