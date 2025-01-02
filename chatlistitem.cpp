#include "chatlistitem.h"
#include "ui_chatlistitem.h"

ChatListItem::ChatListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatListItem)
{
    ui->setupUi(this);

    // test  以后动态加载
    QPixmap pixmap(":/res/head_1.jpg");

    // 缩放图片以适应QLabel的大小
    QPixmap scaledPixmap = pixmap.scaled(ui->IconLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 将缩放后的图片设置到QLabel中
    ui->IconLabel->setPixmap(scaledPixmap);

    ui->IconLabel->show();

}

ChatListItem::~ChatListItem()
{
    delete ui;
}

void ChatListItem::UpdateInfo(const QString &aContactName, const QString &aRecentMsg, const QPixmap &aUserIcon)
{
    mContactName = aContactName;
    mRecentMsg = aRecentMsg;
    mUserIcon = aUserIcon;

    // 缩放图片以适应QLabel的大小
    QPixmap scaledPixmap = mUserIcon.scaled(ui->IconLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // 将缩放后的图片设置到QLabel中
    ui->IconLabel->setPixmap(scaledPixmap);

    ui->Contact->setText(mContactName);
    ui->RecentMsg->setText(mRecentMsg);
}
