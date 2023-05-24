#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : public QSettings
{
	Q_OBJECT
	Q_PROPERTY(QString dbPath READ dbPath WRITE setDbPath NOTIFY dbPathChanged)

public:
				Settings();
	QString		dbPath() const;
	void		setDbPath(const QString & newDbPath);

signals:
	void		dbPathChanged();

};

#endif // SETTINGS_H
