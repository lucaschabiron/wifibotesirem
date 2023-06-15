#include "Robot.h"
#include "VideoWidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QObject>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      m_robot(new Robot(this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_robot;
}

void MainWindow::connectToRobot()
{
    m_robot->connectToRobot();
}

void MainWindow::disconnectFromRobot()
{
    m_robot->disconnectFromRobot();
}

void MainWindow::moveRobotForward()
{
    m_robot->moveForward(170, 170);
}

void MainWindow::moveRobotBackward()
{
    m_robot->moveBackward(170, 170);
}

void MainWindow::turnRobotLeft()
{
    m_robot->turnLeft(170, 170);
}

void MainWindow::turnRobotRight()
{
    m_robot->turnRight(170, 170);
}

void MainWindow::on_move_forward_button_clicked()
{
    moveRobotForward();
}

void MainWindow::on_connect_button_clicked()
{
    connectToRobot();
}

void MainWindow::on_disconnect_button_clicked()
{
    disconnectFromRobot();
}

void MainWindow::on_move_backward_button_clicked()
{
    moveRobotBackward();
}

void MainWindow::on_turn_right_button_clicked()
{
    turnRobotRight();
}

void MainWindow::on_turn_left_button_clicked()
{
    turnRobotLeft();
}

void MainWindow::on_stop_button_clicked()
{
    m_robot->stopMovement();
}

void MainWindow::updateSpeed(int l, int r)
{

    ui->leftSpeed->display(l);
    ui->rightSpeed->display(r);
}

void MainWindow::updateBattery(int battery)
{
    ui->battery->display(battery);
}
