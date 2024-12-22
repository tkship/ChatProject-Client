#ifndef LISTSPACINGITEM_H
#define LISTSPACINGITEM_H

#include <QWidget>

namespace Ui {
class ListSpacingItem;
}

class ListSpacingItem : public QWidget
{
    Q_OBJECT

public:
    explicit ListSpacingItem(QWidget *parent = nullptr);
    ~ListSpacingItem();

private:
    Ui::ListSpacingItem *ui;
};

#endif // LISTSPACINGITEM_H
