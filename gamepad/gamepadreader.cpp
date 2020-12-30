#include "gamepadreader.h"

GamepadReader::GamepadReader(QObject *parent, QTcpSocket* socket, QGamepad* gamepad) : QObject(parent)
{
    this->setParent(parent);
    this->socket = socket;
    this->gamepad = gamepad;
}

void GamepadReader::readGamepad()
{
    socket->write(buildTcpMsg());
}

void GamepadReader::setSocket(QTcpSocket* value)
{
    socket = value;
}

QTcpSocket* GamepadReader::getSocket() const
{
    return socket;
}

QGamepad *GamepadReader::getGamepad() const
{
    return gamepad;
}

void GamepadReader::setGamepad(QGamepad *value)
{
    gamepad = value;
}

QByteArray GamepadReader::buildTcpMsg()
{
    return "It's a TCP msg from gamepad";
}
