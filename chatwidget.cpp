#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);


    //设置头像 未来用户数据中提取 todo
    QPixmap pixmap(":/res/head_2.jpg");

    // 缩放图片以适应QLabel的大小
    QPixmap scaledPixmap = pixmap.scaled(ui->ProfileIcon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 将缩放后的图片设置到QLabel中
    ui->ProfileIcon->setPixmap(scaledPixmap);

    ui->ProfileIcon->show();
}

ChatWidget::~ChatWidget()
{
    delete ui;
}
