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
    void resetData();
    void connectToRobot();
    void disconnectFromRobot();
    void moveForward(short speed1, short speed2);
    void moveBackward(short speed1, short speed2);
    void turnLeft(short speed1, short speed2);
    void turnRight(short speed1, short speed2);
    short Crc16(unsigned char *_Adresse_tab, unsigned char Taille_Max);
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
