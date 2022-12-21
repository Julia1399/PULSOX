#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QWidget::setFixedSize (300,200 );
}

Dialog::~Dialog()
{
    delete ui;

}

void Dialog::on_pushButton_clicked()
{
    close();
}
