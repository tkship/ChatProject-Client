#ifndef CHATLIST_H
#define CHATLIST_H

#include <QListWidget>

class ChatList : public QListWidget
{
    Q_OBJECT
public:
    ChatList(QWidget *parent = nullptr);
    ~ChatList();

protected:
    virtual void enterEvent(QEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
};

#endif // CHATLIST_H
