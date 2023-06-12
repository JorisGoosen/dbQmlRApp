import QtQuick 2.15

Item
{
	RectButton
	{
		text:		"Select outputfolder"
		toolTip:	"Select the folder where the logs, plots and csv will be written.\nShould not exist yet."
		onClicked:	mainModel.switchSomething()
	}
}


/*
	we gaan helemaal niert outputfolder doen.
	gewoon in appdata ofzo
	wel knop om die map te openen ergens




*/
