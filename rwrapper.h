#ifndef RWRAPPER_H
#define RWRAPPER_H

#include <QObject>
#include <RInside.h>

class RWrapper : public QObject
{
  Q_OBJECT

public:
    explicit RWrapper(QObject *parent = nullptr);

  Q_INVOKABLE QString runRCommand(QString command);



signals:

private:
  RInside R;
};

#endif // RWRAPPER_H
