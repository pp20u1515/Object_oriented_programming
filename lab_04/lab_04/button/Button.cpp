#include "Button.hpp"
#include <QDebug>

#include "../defines.hpp"

Button::Button(QWidget *parent) : QPushButton(parent)
{
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(pressSlot()));
    QObject::connect(this, SIGNAL(unpressSignal()), this, SLOT(unpressSlot()));

    state = NOT_ACTIVE;
    currentButtonFloor = 1;
}

void Button::setFloor(int floor)
{
    currentButtonFloor = floor;
}

void Button::pressSlot()
{
    if (this->state == NOT_ACTIVE)
    {
        this->setStyleSheet(QString("background-color:") + COLORBUTTONACTIVE);
        this->update();

        qDebug() << "Call to floor " << this->currentButtonFloor;

        this->state = ACTIVE;
        this->setDisabled(true);

        // Сигнал всем, что нажата данная кнопка
        emit pressSignal(true, this->currentButtonFloor);
    }
}

void Button::unpressSlot()
{
    if (this->state != NOT_ACTIVE)
    {
        this->setStyleSheet((QString("background-color:") + COLORBUTTONINACTIVE));
        this->update();

        this->state = NOT_ACTIVE;
        this->setDisabled(false);
    }
}
