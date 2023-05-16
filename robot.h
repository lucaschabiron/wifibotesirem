#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>

class Robot : public QObject
{
    Q_OBJECT

public:
    explicit Robot(QObject *parent = nullptr);
    ~Robot();

    void connectToRobot(const QString& host, int port);
    void disconnectFromRobot();
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();

};

#endif // ROBOT_H
