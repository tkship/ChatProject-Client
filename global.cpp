#include "global.h"

QString GateServerPrefix = "";
QString WebSocketPrefix = "ws://";

void RePolish(QWidget *aSelf)
{
    aSelf->style()->unpolish(aSelf);
    aSelf->style()->polish(aSelf);
}
