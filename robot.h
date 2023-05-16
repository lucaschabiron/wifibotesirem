#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

class Robot : public QObject
{
    Q_OBJECT

public:
    explicit Robot(QObject *parent = nullptr);
    ~Robot();

    void connectToRobot();
    void disconnectFromRobot();
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();


};

#endif // ROBOT_H
