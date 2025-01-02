#include "chatlistwidget.h"
#include "chatlistitem.h"

#include "global.h"

#include <QWheelEvent>
#include <QScrollBar>


ChatListWidget::ChatListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // test
    for(int i = 0; i < 50; ++i)
    {
        ChatListItem* item = new ChatListItem(this);
        QListWidgetItem* qItem = new QListWidgetItem;
        qItem->setSizeHint({211, 70});
        addItem(qItem);
        setItemWidget(qItem, item);
    }

}

ChatListWidget::~ChatListWidget()
{

}

void ChatListWidget::enterEvent(QEvent *event)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QListWidget::enterEvent(event);
}

void ChatListWidget::leaveEvent(QEvent *event)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QListWidget::leaveEvent(event);
}

void ChatListWidget::wheelEvent(QWheelEvent *event)
{
    int wheelStep = event->angleDelta().y();
    QScrollBar* selfScrollBar = verticalScrollBar();
    selfScrollBar->setValue(selfScrollBar->value() - wheelStep * 0.03);

    // 检查是否滚动到底部
    if(selfScrollBar->value() >= selfScrollBar->maximum())
    {
        // 加载新的列表项... todo
    }

    QListWidget::wheelEvent(event);
}
