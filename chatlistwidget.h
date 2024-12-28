#ifndef CHATLIST_H
#define CHATLIST_H

#include <QListWidget>

class ChatListWidget : public QListWidget
{
    Q_OBJECT
public:
    ChatListWidget(QWidget *parent = nullptr);
    ~ChatListWidget();

protected:
    virtual void enterEvent(QEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
};

#endif // CHATLIST_H
