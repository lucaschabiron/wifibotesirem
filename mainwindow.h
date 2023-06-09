#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class Robot;
class QLineEdit;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateSpeed(int r, int l);
    void updateBattery(int battery);


private slots:

    void connectToRobot();
    void disconnectFromRobot();
    void moveRobotForward();
    void moveRobotBackward();
    void turnRobotLeft();
    void turnRobotRight();

    void on_move_forward_button_clicked();

    void on_connect_button_clicked();

    void on_disconnect_button_clicked();

    void on_move_backward_button_clicked();

    void on_turn_right_button_clicked();

    void on_turn_left_button_clicked();

    void on_stop_button_clicked();

private:
    Ui::MainWindow *ui;
    Robot *m_robot;
};

#endif // MAINWINDOW_H
