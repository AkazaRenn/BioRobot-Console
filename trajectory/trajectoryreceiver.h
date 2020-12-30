#ifndef TRAJECTORYRECEIVER_H
#define TRAJECTORYRECEIVER_H

#include <QObject>
#include <QTcpSocket>

class TrajectoryReceiver : public QObject
{
    Q_OBJECT
public:
    explicit TrajectoryReceiver(QObject *parent = nullptr, QTcpSocket* socket = nullptr, QObject* dataModel = nullptr);

    QTcpSocket *getSocket() const;
    void setSocket(QTcpSocket *value);
    void updateTrajectory();

private:
    QTcpSocket* socket;
    QObject* dataModel;

signals:

};

#endif // TRAJECTORYRECEIVER_H
