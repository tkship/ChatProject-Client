#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(450, 600);

    connect(ui->RegisterButton, &QPushButton::clicked, this, &LoginWidget::SigRegisterButtonClicked);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

