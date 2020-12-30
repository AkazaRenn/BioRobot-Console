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
    QVector<double> data;
    QDataStream stream(socket->readAll());
    stream >> data;
    double xPos = data[0];
    double yPos = data[1];
    double zPos = data[2];
    QMetaObject::invokeMethod(dataModel, "addPoint",
                              Q_ARG(QVariant, QVariant(xPos)),
                              Q_ARG(QVariant, QVariant(yPos)),
                              Q_ARG(QVariant, QVariant(zPos)));
}
