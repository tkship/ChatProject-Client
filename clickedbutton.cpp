#include "clickedbutton.h"

#include "global.h"

ClickedButton::ClickedButton(QWidget* parent)
    : QPushButton(parent)
    , mNormalState("normal")
    , mHoverState("hover")
    , mPressState("press")
{
    setCursor(Qt::PointingHandCursor);
    setProperty("state", mNormalState);
}

ClickedButton::~ClickedButton()
{

}

void ClickedButton::enterEvent(QEvent *event)
{
    setProperty("state", mHoverState);
    RePolish(this);
    QPushButton::enterEvent(event);
}

void ClickedButton::leaveEvent(QEvent *event)
{
    setProperty("state", mNormalState);
    RePolish(this);
    QPushButton::leaveEvent(event);
}

void ClickedButton::mousePressEvent(QMouseEvent *event)
{
    setProperty("state", mPressState);
    RePolish(this);
    QPushButton::mousePressEvent(event);
}

void ClickedButton::mouseReleaseEvent(QMouseEvent *event)
{
    setProperty("state", mNormalState);
    RePolish(this);
    QPushButton::mouseReleaseEvent(event);
}
