#ifndef LISTITEMBASE_H
#define LISTITEMBASE_H

#include <QWidget>

class ChatListItem : public QWidget
{
public:
    ChatListItem(QWidget* parent = nullptr);
    ~ChatListItem();

private:
};

class ContactListItem : public QWidget
{
public:
    ContactListItem(QWidget* parent = nullptr);
    ~ContactListItem();

private:
};

class SpacingItem : public QWidget
{
public:
    SpacingItem(QWidget* parent = nullptr);
    ~SpacingItem();

private:
};

#endif // LISTITEMBASE_H
