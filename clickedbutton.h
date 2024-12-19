#ifndef CLICKEDBUTTON_H
#define CLICKEDBUTTON_H

#include <QPushButton>

// 点击，移动会有变化的button
class ClickedButton : public QPushButton
{
    Q_OBJECT
public:
    ClickedButton(QWidget* parent = nullptr);
    ~ClickedButton();

protected:
    virtual void enterEvent(QEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
private:
    QString mNormalState;
    QString mHoverState;
    QString mPressState;
};

#endif // CLICKEDBUTTON_H
