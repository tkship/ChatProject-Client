#include "timerbtn.h"

#include <QMouseEvent>

TimerBtn::TimerBtn(QWidget* parent, int aTimeOut)
    : QPushButton(parent)
    , mTimeOut(aTimeOut)
    , mCountDown(aTimeOut)
    , mTimer(this)
{
    connect(&mTimer, &QTimer::timeout, this, [this](){
        mCountDown--;
        if(mCountDown < 0)
        {
            mTimer.stop();
            this->setEnabled(true);
            this->setText(mTag);
            mCountDown = mTimeOut;
            return;
        }

        this->setText(QString::number(mCountDown));
    });
}


void TimerBtn::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mTag = this->text();
        mTimer.start(1000);
        this->setEnabled(false);
        this->setText(QString::number(mCountDown));
        emit clicked();
    }


    QPushButton::mouseReleaseEvent(e); // 其他的信号与槽依赖于这个父类事件
}
