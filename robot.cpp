#include "Robot.h"

Robot::Robot(QObject *parent)
    : QObject(parent)
{
    DataToSend.resize(9);
    resetData();
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer


}

Robot::~Robot()
{
}

void Robot::resetData(){
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
}

void Robot::connectToRobot()
{
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

void Robot::updateBattery(){
    float maxVoltage = 10.1; // maximum voltage (battery full)
    float minVoltage = 1.28; // minimum voltage (battery empty)
    float scaleFactor = 4.0; // the original value is scaled down by this factor

    // Convert unsigned char back to voltage (value * scaleFactor)
    float batVoltage = static_cast<float>(static_cast<unsigned char>(DataReceived[2])) * scaleFactor / 100.0;
    float batteryLevel = ((batVoltage - minVoltage) / (maxVoltage - minVoltage)) * 100.0;
    battery = batteryLevel;
}

void Robot::updateSpeed(){
    dataL.SpeedFront=(int)(((unsigned char)DataReceived[1] << 8) + (unsigned char)DataReceived[0]);
    if (dataL.SpeedFront > 32767) dataL.SpeedFront=dataL.SpeedFront-65536;
    dataR.SpeedFront = (int)(((unsigned char)DataReceived[10] << 8) + (unsigned char)DataReceived[9]);
    if (dataR.SpeedFront > 32767) {
        dataR.SpeedFront -= 65536;
    }
}

void Robot::updateIR(){
    dataL.IR = (unsigned char)DataReceived[3];
    dataL.IR2 = (unsigned char)DataReceived[4];
    dataR.IR = (unsigned char)DataReceived[11];
    dataR.IR2 = (unsigned char)DataReceived[12];
}

void Robot::updateInfos(){
    updateBattery();
    updateSpeed();
    updateIR();


    qDebug() << "Battery: " << battery << ", " << "Left Speed: " << dataL.SpeedFront << "Right Speed" << dataR.SpeedFront << "\n" << "Avant Droit: "<< dataR.IR << "Arriere Droit: " << dataR.IR2 << "Avant Gauche: "<< dataL.IR << "Arriere gauche: " << dataL.IR2;
}

void Robot::disconnectFromRobot()
{
    resetData();
    TimerEnvoi->stop();
    socket->close();
}

void Robot::moveForward(short speed1, short speed2)
{
    DataToSend[2] = (unsigned char) speed1;
    DataToSend[4] = (unsigned char) speed2;

    DataToSend[6] = (unsigned char)(80);
    short crc = Crc16((unsigned char *)DataToSend.data()+1,6);
    DataToSend[7] = (unsigned char) crc;
    DataToSend[8] = (unsigned char) (crc >> 8);
}

void Robot::moveBackward(short speed1, short speed2)
{
    DataToSend[2] = (unsigned char) speed1;
    DataToSend[4] = (unsigned char) speed2;

    DataToSend[6] = (unsigned char)(0);
    short crc = Crc16((unsigned char *)DataToSend.data()+1,6);
    DataToSend[7] = (unsigned char) crc;
    DataToSend[8] = (unsigned char) (crc >> 8);
}

void Robot::turnRight(short speed1, short speed2)
{
    DataToSend[2] = (unsigned char) speed1;
    DataToSend[4] = (unsigned char) speed2;

    DataToSend[6] = (unsigned char)(64);
    short crc = Crc16((unsigned char *)DataToSend.data()+1,6);
    DataToSend[7] = (unsigned char) crc;
    DataToSend[8] = (unsigned char) (crc >> 8);
}

void Robot::turnLeft(short speed1, short speed2)
{
    DataToSend[2] = (unsigned char) speed1;
    DataToSend[4] = (unsigned char) speed2;

    DataToSend[6] = (unsigned char)(16);
    short crc = Crc16((unsigned char *)DataToSend.data()+1,6);
    DataToSend[7] = (unsigned char) crc;
    DataToSend[8] = (unsigned char) (crc >> 8);
}

void Robot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void Robot::disconnected() {
    qDebug() << "disconnected...";
}

void Robot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void Robot::readyRead() {
    qDebug() << "reading...";
    DataReceived = socket->readAll();
    updateInfos();
}

void Robot::stopMovement(){
    resetData();

}

void Robot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}



short Robot::Crc16(unsigned char *_Adresse_tab, unsigned char Taille_Max){
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity = 0;

    Crc = 0xFFFF;
    Polynome = 0xA001;
    for (CptOctet=0; CptOctet<Taille_Max;CptOctet++){
        Crc ^= *(_Adresse_tab + CptOctet);

        for(CptBit=0;CptBit<=7;CptBit++){
            Parity = Crc;
            Crc >>=1;
            if(Parity%2 == true) Crc ^= Polynome;
        }
    }
    return (Crc);
}
