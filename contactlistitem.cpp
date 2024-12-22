#include "contactlistitem.h"
#include "ui_contactlistitem.h"

ContactListItem::ContactListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactListItem)
{
    ui->setupUi(this);
}

ContactListItem::~ContactListItem()
{
    delete ui;
}
