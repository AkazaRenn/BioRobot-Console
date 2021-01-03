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
    double joysticks[] = {gamepad->axisLeftX(), gamepad->axisLeftY(), gamepad->axisRightX(), gamepad->axisRightY(),
                         gamepad->buttonL2(), gamepad->buttonR2()};
    char buttons[] = {gamepad->buttonUp(), gamepad->buttonDown(), gamepad->buttonLeft(), gamepad->buttonRight(),
                      gamepad->buttonX(), gamepad->buttonY(), gamepad->buttonA(), gamepad->buttonB(),
                      gamepad->buttonL1(), gamepad->buttonL3(), gamepad->buttonR1(), gamepad->buttonR3(),
                      gamepad->buttonSelect(), gamepad->buttonCenter(), gamepad->buttonStart()};
    char bytes[sizeof(joysticks) * 8 + sizeof(buttons)];
    memcpy(bytes, joysticks, sizeof(joysticks) * sizeof(double));
    memcpy(bytes + sizeof(joysticks) * sizeof(double), buttons, sizeof(buttons));
    return QByteArray(bytes, sizeof(bytes));
}
