#include "resetpwdwidget.h"
#include "ui_resetpwdwidget.h"

ResetPwdWidget::ResetPwdWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResetPwdWidget)
{
    ui->setupUi(this);
}

ResetPwdWidget::~ResetPwdWidget()
{
    delete ui;
}
