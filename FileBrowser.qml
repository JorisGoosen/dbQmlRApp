import QtQuick
import Qt.labs.platform

FileDialog
{
	id: fileDialog
	title: "Please choose a file"
	folder: StandardPaths.writableLocation(StandardPaths.DownloadLocation)

	/*onAccepted:
	{
		console.log("You chose: " + fileDialog.fileUrls)
	}

	onRejected: {
		console.log("Canceled")
	}*/
}
