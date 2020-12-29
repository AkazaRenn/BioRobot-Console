#ifndef READINPUT_H
#define READINPUT_H

#include <QThread>
#include <QVector>
#include <QTimer>
#include <QVariant>

class ReadInput : public QThread
{
    Q_OBJECT
public:
    explicit ReadInput(QObject *parent);
    void run();
};

#endif // READINPUT_H
