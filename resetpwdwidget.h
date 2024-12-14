#ifndef RESETPWDWIDGET_H
#define RESETPWDWIDGET_H

#include <QWidget>

namespace Ui {
class ResetPwdWidget;
}

class ResetPwdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResetPwdWidget(QWidget *parent = nullptr);
    ~ResetPwdWidget();

private:
    Ui::ResetPwdWidget *ui;
};

#endif // RESETPWDWIDGET_H
