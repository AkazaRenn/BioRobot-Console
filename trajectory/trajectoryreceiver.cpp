#include "trajectory/trajectoryreceiver.h"

#include <QDataStream>
#include <cmath>

TrajectoryReceiver::TrajectoryReceiver(QObject *parent, QTcpSocket* socket, QObject* dataModel)
{
    this->setParent(parent);
    this->socket = socket;
    this->dataModel = dataModel;
    t = -1;
    currX = currY = currZ = 0;
    velX = velY = velZ = 0;
    count = 0;
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

    double array[DATA_IN_PACKET][4];
    memcpy(array, data, sizeof(double) * DATA_IN_PACKET * 4);
    for(int i = 0; i < DATA_IN_PACKET; i++) {
        if(t != -1) {
            double tDiff = array[i][0] - t;
//            if(abs(array[i][1] - X_SHIFT) > 0.2)
//                velX += tDiff * -1 * (array[i][1] - X_SHIFT);
//            currX += tDiff * velX;
//            if(abs(array[i][2] - Y_SHIFT) > 0.2)
//                velY += tDiff * -1 * (array[i][2] - Y_SHIFT);
//            currY += tDiff * velY;
//            if(abs(array[i][3] - Z_SHIFT) > 0.2)
//                velZ += tDiff * -1 * (array[i][3] - Z_SHIFT);
//            currZ += tDiff * velZ;
            currX += tDiff * tDiff * array[i][1];
            currY += tDiff * tDiff * array[i][2];
            currZ += tDiff * tDiff * array[i][3];
        }
        t = array[i][0];
    }
    if(count++ >= PACKET_NUM) {
//        printf("t: %.4f, x: %.4f, y: %.4f, z: %.4f\n", t, currX, currY, currZ);
        QMetaObject::invokeMethod(dataModel, "addPoint",
                                  Q_ARG(QVariant, QVariant(currX)),
                                  Q_ARG(QVariant, QVariant(currY)),
                                  Q_ARG(QVariant, QVariant(currZ)));
        count = 0;
    }
}
