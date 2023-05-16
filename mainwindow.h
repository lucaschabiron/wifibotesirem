#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Robot;
class VideoWidget;
class QLineEdit;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connectToRobot();
    void disconnectFromRobot();
    void moveRobotForward();
    void moveRobotBackward();
    void turnRobotLeft();
    void turnRobotRight();

private:
    Robot* m_robot;
    VideoWidget* m_videoWidget;
    QLineEdit* m_hostLineEdit;
    QLineEdit* m_portLineEdit;
    QPushButton* m_connectButton;
    QPushButton* m_disconnectButton;
    QPushButton* m_forwardButton;
    QPushButton* m_backwardButton;
    QPushButton* m_leftButton;
    QPushButton* m_rightButton;
};

#endif // MAINWINDOW_H
