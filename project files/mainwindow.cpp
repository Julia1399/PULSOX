#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QSerialPortInfo>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this); // это не трогаем
    QWidget::setFixedSize (804,550 );

    // создали таймер, привязали его к форме
    // если ругается на QTimer ставим на него курсор и нажимаем Alt+Enter
    // чтоб на автомате добавить #include <QTimer>
    //QTimer *timer = new QTimer(this);

    // подключили сигнал timeout, к слоту нажатия на кнопку
     //****connect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_10_clicked()));

    // запускаем со значением вызывать раз в 300мс
   //timer->start(300);
    dt = QDateTime::currentDateTime();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        {
            ui->cmbPort->addItem(serialPortInfo.portName());
            statusBar()->showMessage(dt.toString("dd.MM.yyyy")+ " | " + serialPortInfo.portName());
        }
    const auto infos = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &info : infos) {
            qDebug() << info.portName();
        }
    ui->spo2->setReadOnly(true);
    ui->BPM->setReadOnly(true);
    ui->temp->setReadOnly(true);


}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_clicked()
{

    // создали экземпляр для общения по последовательному порту
    QSerialPort serialPort;

    // указали имя к какому порту будем подключаться
   serialPort.setPortName(this->ui->cmbPort->currentText());
    // указали скорость
    serialPort.setBaudRate(QSerialPort::Baud9600);

    // пробуем подключится
    if (!serialPort.open(QIODevice::ReadWrite)) {
        // если подключится не получится, то покажем сообщение с ошибкой
        QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
        return;
    }

    // отправляем строку с b нашей арудинкой
    serialPort.write("b"); // очень важно, что именно двойные кавычки
    serialPort.waitForBytesWritten(); // ждем пока дойдет

    // и не знаю с чем тут связано, но, чтобы сообщение дошло
    // надо обязательно прочитать не пришло ли нам чего в ответ
    //
    // функция waitForReadyRead(10) проверят не появилось
    // в ближайшие 10 миллисекунд чего-нибудь в ответ
    while (serialPort.waitForReadyRead(10)) {
        // и если появилось мы просто это читаем в пустоту
        serialPort.readAll();

        // сам while необходим для того что ответ приходит порциями
        // и мы хотим считать все что отправилось
    }

    // ну и закрываем порт
    serialPort.close();
}



void MainWindow::on_pushButton_3_clicked()
{

    // создали экземпляр для общения по последовательному порту
    QSerialPort serialPort;

    // указали имя к какому порту будем подключаться
   serialPort.setPortName(this->ui->cmbPort->currentText());
    // указали скорость
    serialPort.setBaudRate(QSerialPort::Baud9600);

    // пробуем подключится
    if (!serialPort.open(QIODevice::ReadWrite)) {
        // если подключится не получится, то покажем сообщение с ошибкой
        QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
        return;
    } else {

        QMessageBox::information(this, "Сообщение", "Подключено к " + serialPort.portName());
    }

//    QSerialPort serialPort;

//   serialPort.setPortName(this->ui->cmbPort->currentText());
//    serialPort.setBaudRate(QSerialPort::Baud9600);

//    if (!serialPort.open(QIODevice::ReadWrite)) {
//        // закомментим вызовы QMessageBox, так как эта функция будет вызываться таймером
//        // и информационное сообщение будет блокировать работу программы
//        //QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
//        return; // просто оставляем ретёрн, типа не подключились ну и бог с ним
//    }

//    serialPort.write("p"); // меняем тут на p
//    serialPort.waitForBytesWritten();

//    QByteArray data;
//    while (serialPort.waitForReadyRead(10)) {
//        data.append(serialPort.readAll());
//    }

//    // тут вставляем значение в txtLight

//    serialPort.close();
}

void MainWindow::on_pushButton_7_clicked()
{
    qApp->exit();
}

void MainWindow::on_pushButton_6_clicked()
{
    dialog.show();
}


void MainWindow::on_pushButton_5_clicked()
{
    form.show();
}



void MainWindow::on_pushButton_8_clicked()
{

    QSerialPort serialPort;

        serialPort.setPortName(this->ui->cmbPort->currentText());
        serialPort.setBaudRate(QSerialPort::Baud115200);

        if (!serialPort.open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
            return;
        }


        serialPort.write("s");
        serialPort.waitForBytesWritten();


        QByteArray data;  // специальный тип QT для хранения последовательности байтов
        while (serialPort.waitForReadyRead(100)) {
            // вместо холостого чтения накапливаем результат в переменную data
            data.append(serialPort.readAll());
        }

        qDebug() << dec;
        // добавляем строку с содержимым data в поле txtOutput
        ui->textBrowser->append(dt.toString("dd.MM.yyyy hh:mm"));
        ui->textBrowser->append("SpO2: " + data + " %");
        ui->spo2->setText(data + " %");

        serialPort.close();
}

void MainWindow::on_pushButton_10_clicked()
{

    QSerialPort serialPort;

        serialPort.setPortName(this->ui->cmbPort->currentText());
        serialPort.setBaudRate(QSerialPort::Baud115200);

        if (!serialPort.open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
            return;
        }


        serialPort.write("b");
        serialPort.waitForBytesWritten();


        QByteArray data;  // специальный тип QT для хранения последовательности байтов
        while (serialPort.waitForReadyRead(100)) {
            // вместо холостого чтения накапливаем результат в переменную data
            data.append(serialPort.readAll());
        }

        int dec = data.toFloat();
        data.setNum(dec);
        // добавляем строку с содержимым data в поле txtOutput
        ui->textBrowser->append(dt.toString("dd.MM.yyyy hh:mm"));
        ui->textBrowser->append("ЧСС: " + data + " уд/мин");
        ui->BPM->setText(data + " уд/мин");

        serialPort.close();

}

void MainWindow::on_pushButton_11_clicked()
{


    QSerialPort serialPort;

        serialPort.setPortName(this->ui->cmbPort->currentText());
        serialPort.setBaudRate(QSerialPort::Baud115200);

        if (!serialPort.open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
            return;
        }

        ui->textBrowser->append(dt.toString("dd.MM.yyyy hh:mm"));
        serialPort.write("b");
        serialPort.waitForBytesWritten();


        QByteArray data_1;  // специальный тип QT для хранения последовательности байтов
        while (serialPort.waitForReadyRead(100)) {
            // вместо холостого чтения накапливаем результат в переменную data
            data_1.append(serialPort.readAll());
        }

        qDebug() << data_1;
        int dec_1 = data_1.toFloat();
        data_1.setNum(dec_1);
        // добавляем строку с содержимым data в поле txtOutput
        ui->textBrowser->append("ЧСС: " + data_1 + " уд/мин");
        ui->BPM->setText(data_1 + " уд/мин");


        serialPort.write("p");
        serialPort.waitForBytesWritten();




        QByteArray data_2;  // специальный тип QT для хранения последовательности байтов
        while (serialPort.waitForReadyRead(100)) {
            // вместо холостого чтения накапливаем результат в переменную data
            data_2.append(serialPort.readAll());
        }
        int dec = data_2.toFloat();
        data_2.setNum(dec);
        // добавляем строку с содержимым data в поле txtOutput
        ui->textBrowser->append("t: " + data_2 + " °C");
        ui->temp->setText(data_2 + " °C");

        serialPort.write("s");
        serialPort.waitForBytesWritten();


        QByteArray data;  // специальный тип QT для хранения последовательности байтов
        while (serialPort.waitForReadyRead(100)) {
            // вместо холостого чтения накапливаем результат в переменную data
            data.append(serialPort.readAll());
        }
        qDebug() << data;

        // добавляем строку с содержимым data в поле txtOutput
        ui->textBrowser->append("SpO2: " + data + " %");
        ui->spo2->setText(data + " %");

        serialPort.close();

}

void MainWindow::on_pushButton_9_clicked()
{

    QSerialPort serialPort;

        serialPort.setPortName(this->ui->cmbPort->currentText());
        serialPort.setBaudRate(QSerialPort::Baud115200);

        if (!serialPort.open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
            return;
        }

        serialPort.write("p");
        serialPort.waitForBytesWritten();
        // ВСЕ ЧТО ВЫШЕ ЭТОГО НЕ ТРОГАЕМ

        QByteArray data;  // специальный тип QT для хранения последовательности байтов
        while (serialPort.waitForReadyRead(100)) {
            // вместо холостого чтения накапливаем результат в переменную data
            data.append(serialPort.readAll());
        }
        int dec = data.toFloat();
        data.setNum(dec);
        // добавляем строку с содержимым data в поле txtOutput
        ui->textBrowser->append(dt.toString("dd.MM.yyyy hh:mm"));
        ui->textBrowser->append("t: " + data + " °C");
        ui->temp->setText(data + " °C");
        serialPort.close();

}

void MainWindow::on_pushButton_2_clicked()
{
     ui->textBrowser->clear();
     ui->BPM->clear();
     ui->temp->clear();
     ui->spo2->clear();
}

void MainWindow::on_action_3_triggered()
{
    qApp->exit();
}

void MainWindow::on_action_2_triggered()
{
    ui->textBrowser->clear();
}

void MainWindow::on_actionAbout_triggered()
{
    dialog.show();
}

void MainWindow::on_action_4_triggered()
{
    form.show();
}

void MainWindow::on_pushButton_4_clicked()
{
    QSerialPort serialPort;

        serialPort.setPortName(this->ui->cmbPort->currentText());


        if (!serialPort.open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
            return;
        } else {
            QMessageBox::information(this, "Сообщение", "Список COM-портов обновлён");
        }

}

void MainWindow::on_action_triggered()
{
    QSerialPort serialPort;

        serialPort.setPortName(this->ui->cmbPort->currentText());


        if (!serialPort.open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
            return;
        } else {
            QMessageBox::information(this, "Сообщение", "Список COM-портов обновлён");
        }
}

void MainWindow::on_action_5_triggered()
{
    QSerialPort serialPort;

    // указали имя к какому порту будем подключаться
   serialPort.setPortName(this->ui->cmbPort->currentText());
    // указали скорость
    serialPort.setBaudRate(QSerialPort::Baud9600);
    // пробуем подключится
    if (!serialPort.open(QIODevice::ReadWrite)) {
        // если подключится не получится, то покажем сообщение с ошибкой
        QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
        return;
    } else {

        QMessageBox::information(this, "Сообщение", "Подключено к " + serialPort.portName());
    }
}
