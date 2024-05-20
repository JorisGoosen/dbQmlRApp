#ifndef RWRAPPER_H
#define RWRAPPER_H

#include <QObject>
#include <RInside.h>

class RWrapper : public QObject
{
  Q_OBJECT

	Q_PROPERTY(QStringList	prevOutput			READ prevOutput			WRITE setPrevOutput NOTIFY prevOutputChanged	)
	Q_PROPERTY(QString		prevOutputConcat	READ prevOutputConcat						NOTIFY prevOutputChanged	)
	Q_PROPERTY(int			plotWidth			READ plotWidth			WRITE setPlotWidth	NOTIFY plotWidthChanged		)
	Q_PROPERTY(int			plotHeight			READ plotHeight			WRITE setPlotHeight NOTIFY plotHeightChanged	)
	Q_PROPERTY(QString		error				READ error				WRITE setError		NOTIFY errorChanged			)

public:
    explicit RWrapper(QObject *parent = nullptr);

	QStringList prevOutput()		const;
	QString		prevOutputConcat()	const { return prevOutput().join("\n"); }
	void		setPrevOutput(const QStringList & newPrevOutput);

	int plotWidth() const;
	int plotHeight() const;

	void setPlotWidth(int newPlotWidth);
	void setPlotHeight(int newPlotHeight);
	
	QString error() const;
	void	setError(const QString &newError);
	
public slots:
	QString runRCommand(	QString		command);
	QString runRCommands(	QStringList	commands);

signals:
	void prevOutputChanged();
	void plotWidthChanged(int w);
	void plotHeightChanged(int h);
	
	void errorChanged();
	
private:
	RInside		*	R = nullptr;
	QStringList		_prevOutput = { "QML R SQLite app" };
	int				_plotWidth	= 500,
					_plotHeight	= 300;
	QString _error;
};

#endif // RWRAPPER_H
