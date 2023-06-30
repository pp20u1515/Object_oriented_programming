#include "Lift.hpp"

Lift::Lift(QObject *parent) : QObject(parent)
{
    QObject::connect(&cabin, SIGNAL(cabinFinished(bool)), &controller, SLOT(newTarget(bool)));
    QObject::connect(&controller, SIGNAL(moveCabinSignal()), &cabin, SLOT(moveCabin()));
    QObject::connect(&controller, SIGNAL(stopCabinSignal()), &cabin, SLOT(stopCabin()));
}

QWidget *Lift::widget()
{
    return &controller;
}
