#include "Cabin.hpp"
#include <QDebug>

#include "defines.hpp"

Cabin::Cabin(QObject *parent) : QObject(parent)
{
    state = STOP;

    QObject::connect(this, SIGNAL(openDoors()), &doors, SLOT(startOpening()));
    QObject::connect(&moveTimer, SIGNAL(timeout()), this, SLOT(free()));
    QObject::connect(&doors, SIGNAL(doorClosed()), this, SLOT(free()));
}

void Cabin::stopCabin()
{
        state = WAIT;

        moveTimer.stop();
        emit openDoors();
 }

void Cabin::moveCabin()
{
    if (state == STOP || state == MOVING)
    {
        state = MOVING;
        moveTimer.start(MOVE_TIME);
    }
}

void Cabin::free()
{
    if (state != STOP)
    {
        state = STOP;
        emit cabinFinished(false);
    }
}



