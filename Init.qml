import QtQuick 2
import QtQuick.Controls 2
import QtQuick.Layouts

Item
{
	RowLayout
	{
		RectButton
		{
			text:		"Select exisiting database"
			toolTip:	"This is probably in your dropbox or other shared folder."
			onClicked:	mainModel.selectDatabase()
		}

		RectButton
		{
			text:		"Create new temporary database"
			toolTip:	"Testing testing!"
			onClicked:	mainModel.testDatabase()
		}
	}

}
