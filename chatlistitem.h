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

    void UpdateInfo(const QString& aContactName, const QString& aRecentMsg, const QPixmap& aUserIcon);
private:
    Ui::ChatListItem *ui;

    QString mContactName;
    QPixmap mUserIcon;
    QString mRecentMsg;
};

#endif // CHATLISTITEM_H
