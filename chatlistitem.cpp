#include "chatlistitem.h"
#include "ui_chatlistitem.h"

ChatListItem::ChatListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatListItem)
{
    ui->setupUi(this);
}

ChatListItem::~ChatListItem()
{
    delete ui;
}
