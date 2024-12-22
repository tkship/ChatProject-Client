#ifndef CHATLISTITEM_H
#define CHATLISTITEM_H

#include <QWidget>

namespace Ui {
class ChatListItem;
}

class ChatListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ChatListItem(QWidget *parent = nullptr);
    ~ChatListItem();

private:
    Ui::ChatListItem *ui;
};

#endif // CHATLISTITEM_H
