#include "listspacingitem.h"
#include "ui_listspacingitem.h"

ListSpacingItem::ListSpacingItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListSpacingItem)
{
    ui->setupUi(this);
}

ListSpacingItem::~ListSpacingItem()
{
    delete ui;
}
