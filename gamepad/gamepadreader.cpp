#include "gamepadreader.h"

GamepadReader::GamepadReader(QObject *parent) : QObject(parent)
{
}

void GamepadReader::readGamepad()
{

    printf("read!");
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
