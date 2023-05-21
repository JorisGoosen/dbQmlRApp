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

public:
    explicit RWrapper(QObject *parent = nullptr);

	Q_INVOKABLE QString runRCommand(QString command);

	QStringList prevOutput()		const;
	QString		prevOutputConcat()	const { return prevOutput().join("\n"); }
	void		setPrevOutput(const QStringList & newPrevOutput);

	int plotWidth() const;
	int plotHeight() const;

	void setPlotWidth(int newPlotWidth);
	void setPlotHeight(int newPlotHeight);

signals:
	void prevOutputChanged();
	void plotWidthChanged();
	void plotHeightChanged();

private:
	RInside		*	R = nullptr;
	QStringList		_prevOutput = { "QML R SQLite app" };
	int				_plotWidth	= 500,
					_plotHeight	= 300;
};

#endif // RWRAPPER_H
