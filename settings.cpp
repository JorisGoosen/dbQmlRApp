#include "settings.h"

Settings::Settings()
{

}

QString Settings::dbPath() const
{
	return value("dbPath", "").toString();
}

void Settings::setDbPath(const QString & newDbPath)
{
	if (dbPath() == newDbPath)
		return;

	setValue("dbPath", newDbPath);
	emit dbPathChanged();
}
