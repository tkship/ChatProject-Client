#include "chatlist.h"
#include "chatlistitem.h"

#include <QWheelEvent>
#include <QScrollBar>


ChatList::ChatList(QWidget *parent)
    : QListWidget(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // test
    for(int i = 0; i < 10; ++i)
    {
        ChatListItem* item = new ChatListItem;
        QListWidgetItem* qItem = new QListWidgetItem;
        qItem->setSizeHint({211, 70});
        addItem(qItem);
        setItemWidget(qItem, item);
    }


}

ChatList::~ChatList()
{

}

void ChatList::enterEvent(QEvent *event)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QListWidget::enterEvent(event);
}

void ChatList::leaveEvent(QEvent *event)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QListWidget::leaveEvent(event);
}

void ChatList::wheelEvent(QWheelEvent *event)
{
    int wheelStep = event->angleDelta().y();
    // 像这种scrollBar居然要另包头文件
    // 这么设计大概是为了解耦，减少编译项
    // 但这是怎么做到的呢？ 类成员只用指针？ 然后头文件只有声明？ 应该是这样
    QScrollBar* selfScrollBar = verticalScrollBar();
    selfScrollBar->setValue(selfScrollBar->value() - wheelStep);

    // 检查是否滚动到底部
    if(selfScrollBar->value() >= selfScrollBar->maximum())
    {
        // 加载新的列表项... todo
    }

    QListWidget::wheelEvent(event);
}
