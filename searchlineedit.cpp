#include "searchlineedit.h"

#include "global.h"

SearchLineEdit::SearchLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setPlaceholderText("搜索");

    // 最大字符数
    setMaxLength(26);

    // 放大镜图标
    QAction* searchAction = new QAction(this);
    searchAction->setIcon(QIcon(":/res/search.png"));
    addAction(searchAction, QLineEdit::LeadingPosition);

    // 末尾的清除图标
    QAction* clearAction = new QAction(this);
    clearAction->setIcon(QIcon(":/res/close_transparent.png"));
    addAction(clearAction, QLineEdit::TrailingPosition);
    // 有文字时显示出来
    connect(this, &QLineEdit::textChanged, [clearAction](const QString& aText){
        if(aText.isEmpty())
        {
            clearAction->setIcon(QIcon(":/res/close_transparent.png"));
        }
        else
        {
            clearAction->setIcon(QIcon(":/res/close_search.png"));
        }
    });
    // 点击时清空text
    connect(clearAction, &QAction::triggered, [this, clearAction](){
        clear();
        clearAction->setIcon(QIcon(":/res/close_transparent.png"));
        clearFocus();
    });

}

SearchLineEdit::~SearchLineEdit()
{

}
