#include "MainWindow.h"
#include "Robot.h"
#include "VideoWidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_robot(new Robot(this)),
    m_videoWidget(new VideoWidget(this)),
    m_hostLineEdit(new QLineEdit(this)),
    m_portLineEdit(new QLineEdit(this)),
    m_connectButton(new QPushButton("Connect", this)),
    m_disconnectButton(new QPushButton("Disconnect", this)),
    m_forwardButton(new QPushButton("Forward", this)),
    m_backwardButton(new QPushButton("Backward", this)),
    m_leftButton(new QPushButton("Left", this)),
    m_rightButton(new QPushButton("Right", this))
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(m_hostLineEdit);
    layout->addWidget(m_portLineEdit);
    layout->addWidget(m_connectButton);
    layout->addWidget(m_disconnectButton);
    layout->addWidget(m_forwardButton);
    layout->addWidget(m_backwardButton);
    layout->addWidget(m_leftButton);
    layout->addWidget(m_rightButton);

    QWidget* widget = new QWidget(this);
    widget->setLayout(layout);
    setCentralWidget(widget);

    connect(m_connectButton, &QPushButton::clicked, this, &MainWindow::connectToRobot);
    connect(m_disconnectButton, &QPushButton::clicked, this, &MainWindow::disconnectFromRobot);
    connect(m_forwardButton, &QPushButton::clicked, this, &MainWindow::moveRobotForward);
    connect(m_backwardButton, &QPushButton::clicked, this, &MainWindow::moveRobotBackward);
    connect(m_leftButton, &QPushButton::clicked, this, &MainWindow::turnRobotLeft);
    connect(m_rightButton, &QPushButton::clicked, this, &MainWindow::turnRobotRight);
}

MainWindow::~MainWindow()
{
    delete m_robot;
    delete m_videoWidget;
    delete m_hostLineEdit;
    delete m_portLineEdit;
    delete m_connectButton;
    delete m_disconnectButton;
    delete m_forwardButton;
    delete m_backwardButton;
    delete m_leftButton;
    delete m_rightButton;
}

void MainWindow::connectToRobot()
{
    QString host = m_hostLineEdit->text();
    int port = m_portLineEdit->text().toInt();
    m_robot->connectToRobot(host, port);
}

void MainWindow::disconnectFromRobot()
{
    m_robot->disconnectFromRobot();
}

void MainWindow::moveRobotForward()
{
    m_robot->moveForward();
}

void MainWindow::moveRobotBackward()
{
    m_robot->moveBackward();
}

void MainWindow::turnRobotLeft()
{
    m_robot->turnLeft();
}

void MainWindow::turnRobotRight()
{
    m_robot->turnRight();
}

