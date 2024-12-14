#ifndef TIMERBTN_H
#define TIMERBTN_H

#include <QPushButton>
#include <QTimer>

class TimerBtn : public QPushButton
{
    Q_OBJECT

public:
    TimerBtn(QWidget* parent = nullptr, int aTimeOut = 10);

    void mouseReleaseEvent(QMouseEvent* e) override;

private:
    int mTimeOut;
    int mCountDown;
    QString mTag;
    QTimer mTimer;

};

#endif // TIMERBTN_H
