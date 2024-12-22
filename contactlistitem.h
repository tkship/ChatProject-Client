#ifndef CONTACTLISTITEM_H
#define CONTACTLISTITEM_H

#include <QWidget>

namespace Ui {
class ContactListItem;
}

class ContactListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ContactListItem(QWidget *parent = nullptr);
    ~ContactListItem();

private:
    Ui::ContactListItem *ui;
};

#endif // CONTACTLISTITEM_H
