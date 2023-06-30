#include "Doors.hpp"
#include "../defines.hpp"
#include <QDebug>

Doors::Doors() : state(CLOSED)
{
    QObject::connect(&openTimer, SIGNAL(timeout()), this, SLOT(open()));
    QObject::connect(&waitTimer,  SIGNAL(timeout()), this, SLOT(startClosing()));
    QObject::connect(&closeTimer, SIGNAL(timeout()), this, SLOT(close()));
}

void Doors::startOpening()
{
    // Если двери не закрыты и не закрываются, то начать открывать её не можем
    if (!(state == CLOSED || state == CLOSING)) return;

    this->state = OPENING;
    qDebug() << "Doors are opening...";

    if (state == OPENING)
    {
        this->openTimer.start(DOOR_TIME);
    }
    else
    {
        auto timer = this->closeTimer.remainingTime();
        closeTimer.stop();
        this->openTimer.start(DOOR_TIME - timer);
    }
}

void Doors::open()
{
    if (this->state != OPENING) return;

    this->state = OPEN;
    qDebug() << "Doors are open!";
    this->waitTimer.start(WAIT_TIME);
}

void Doors::close()
{
    if (this->state != CLOSING) return;
    this->state = CLOSED;
    qDebug() << " The doors have closed!";

    emit doorClosed();
}

void Doors::startClosing()
{
    if (this->state != OPEN) return;
    this->state = CLOSING;
    qDebug() << "Doors are closing...";
    this->closeTimer.start(DOOR_TIME);
}
