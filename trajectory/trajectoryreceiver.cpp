#include "trajectory/trajectoryreceiver.h"

#include <QDataStream>

TrajectoryReceiver::TrajectoryReceiver(QObject *parent, QTcpSocket* socket, QObject* dataModel)
{
    this->setParent(parent);
    this->socket = socket;
    this->dataModel = dataModel;
}

QTcpSocket *TrajectoryReceiver::getSocket() const
{
    return socket;
}

void TrajectoryReceiver::setSocket(QTcpSocket *value)
{
    socket = value;
}

void TrajectoryReceiver::updateTrajectory()
{
    QByteArray data = socket->readAll();
    double array[3];
    memcpy(array, data, data.size());
    printf("Adding x: %.4f, y: %.4f, z: %.4f\n", array[0], array[1], array[2]);
    QMetaObject::invokeMethod(dataModel, "addPoint",
                              Q_ARG(QVariant, QVariant(array[0])),
                              Q_ARG(QVariant, QVariant(array[1])),
                              Q_ARG(QVariant, QVariant(array[2])));
}
