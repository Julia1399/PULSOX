#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialog.h>
#include <QDateTime>
#include <QSerialPortInfo>
#include <form.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_2_clicked();

    void on_action_3_triggered();

    void on_action_2_triggered();

    void on_actionAbout_triggered();

    void on_action_4_triggered();

    void on_pushButton_4_clicked();

    void on_action_triggered();

    void on_action_5_triggered();

private:
    Ui::MainWindow *ui;
    Dialog dialog;
    QDateTime dt;
    QSerialPortInfo serialPortInfo;
    Form form;
};

#endif // MAINWINDOW_H
