#ifndef GAMEPADREADER_H
#define GAMEPADREADER_H

#include <QObject>
#include <QTcpSocket>
#include <QGamepad>

class GamepadReader : public QObject
{
    Q_OBJECT
public:
    explicit GamepadReader(QObject *parent = nullptr, QTcpSocket* socket = nullptr, QGamepad* gamepad = nullptr);
    void readGamepad();

    void setSocket(QTcpSocket* value);
    QTcpSocket* getSocket() const;

    QGamepad *getGamepad() const;
    void setGamepad(QGamepad *value);

private:
    QTcpSocket* socket;
    QGamepad* gamepad;
    QByteArray buildTcpMsg();

signals:

};

#endif // GAMEPADREADER_H
