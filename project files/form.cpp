#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    QWidget::setFixedSize (800,740);
}

Form::~Form()
{
    delete ui;
}
