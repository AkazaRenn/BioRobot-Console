#ifndef TRAJECTORYRECEIVER_H
#define TRAJECTORYRECEIVER_H

#include <QObject>
#include <QTcpSocket>

#define DATA_IN_PACKET 25
#define PACKET_NUM 4
//#define PACKET_BUCKET 1
#define X_SHIFT 1.7346685346313342
#define Y_SHIFT -0.43659536199828847
#define Z_SHIFT 11.465409892155844

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
    double t;
    double currX, currY, currZ;
    double velX, velY, velZ;
    int count;

signals:

};

#endif // TRAJECTORYRECEIVER_H
