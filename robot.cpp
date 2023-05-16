#include "Robot.h"

Robot::Robot(QObject *parent)
    : QObject(parent)
{
    // Here, you can establish connections to the tcpSocket and udpSocket signals
    // For example, connect to the readyRead() signal to read incoming data
}

Robot::~Robot()
{
}

void Robot::connectToRobot(const QString& host, int port)
{
    // Connect to the robot here
    // For example: m_tcpSocket.connectToHost(host, port);
}

void Robot::disconnectFromRobot()
{
    // Disconnect from the robot here
    // For example: m_tcpSocket.disconnectFromHost();
}

void Robot::moveForward()
{
}

void Robot::moveBackward()
{
}

void Robot::turnLeft()
{
}

void Robot::turnRight()
{
}
