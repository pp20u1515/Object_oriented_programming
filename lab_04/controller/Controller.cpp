#include "Controller.hpp"

#include <QLabel>
#include <QDebug>

Controller::Controller(QWidget *parent) : QWidget(parent)
{
    this->layout = std::make_unique<QVBoxLayout>();
    this->setLayout(this->layout.get());

    auto new_button = std::make_shared<Button>();
    new_button->setDisabled(true);
    new_button->setStyleSheet("background-color:white; color:black");
    new_button->setFloor(FLOORS + 1);
    new_button->setText("Floor Buttons");

    this->buttons_floor.insert(this->buttons_floor.begin(), new_button);
    layout->addWidget(dynamic_cast<QPushButton *>(new_button.get()));

    for (size_t i = 0; i < FLOORS; i++)
    {

        auto new_button = std::make_shared<Button>();
        new_button->setFloor(FLOORS - i);
        new_button->setText(QString::number(FLOORS - i));
        new_button->setStyleSheet(QString("background-color:") + COLORBUTTONINACTIVE);

        this->buttons_floor.insert(this->buttons_floor.begin(), new_button);
        layout->addWidget(dynamic_cast<QPushButton *>(new_button.get()));

        is_visit.push_back(false);

        QObject::connect(new_button.get(), SIGNAL(pressSignal(bool,int)), this, SLOT(newTarget(bool,int)));
    }

    auto lift_button = std::make_shared<Button>();
    lift_button->setDisabled(true);
    lift_button->setStyleSheet("background-color:white; color:black");
    lift_button->setFloor(2 * FLOORS + 2);
    lift_button->setText("Lift Buttons");
    this->buttons_lift.insert(this->buttons_lift.begin(), lift_button);
    layout->addWidget(dynamic_cast<QPushButton *>(lift_button.get()));


    for (size_t i = 0; i < FLOORS; i++)
    {
        auto button = std::make_shared<Button>();
        button->setFloor(FLOORS - i);
        button->setText(QString::number(FLOORS - i));
        button->setStyleSheet(QString("background-color:") + COLORBUTTONINACTIVE);

        this->buttons_lift.insert(this->buttons_lift.begin(), button);
        layout->addWidget(dynamic_cast<QPushButton *>(button.get()));

        is_visit.push_back(false);

        QObject::connect(button.get(), SIGNAL(pressSignal(bool,int)), this, SLOT(newTarget(bool,int)));
    }


    QObject::connect(this, SIGNAL(reachFloorSignal()), this, SLOT(reachFloor()));
}

void Controller::newTarget(bool got_new, int floor)
{
    this->state = BUSY;

    if (got_new)
    {
        this->is_visit[floor - 1] = true;

        identifyNewTarget(floor);
        targetFloor = floor;
        decideDirection();

        if (direction == STAY)
        {
            emit reachFloorSignal();
        }
        else
        {
            emit moveCabinSignal();
        }
    }
    else if (identifyNewTarget(floor))
    {
        targetFloor = floor;
        decideDirection();

        if (direction != STAY)
        {
            updateFloor();
            emit moveCabinSignal();
        }
        else
        {
            emit reachFloorSignal();
        }
     }
}

void Controller::decideDirection()
{
    if (targetFloor > curFloor)
    {
        direction = UP;
    }
    else if (targetFloor < curFloor)
    {
        direction = DOWN;
    }
    else
    {
        last_direction = direction;
        direction = STAY;
    }
}

bool Controller::identifyNewTarget(int &new_target)
{
    bool rc = false;
    Direction dir;

    if (direction != STAY)
        dir = direction;
    else
        dir = (last_direction == STAY) ? UP: last_direction;

    for (int i = curFloor; !rc && i <= FLOORS && i > 0; i = i + dir)
        if (is_visit[i - 1])
        {
            new_target = i;
            rc = true;
        }

    if (!rc)
    {
        dir = ((dir == UP) ? DOWN : UP);

        for (int i = curFloor; !rc && i <= FLOORS && i > 0; i = i + dir)
        {
            if (is_visit[i - 1])
            {
                new_target = i;
                rc = true;
            }
        }
    }

    return rc;
}

void Controller::reachFloor()
{
    if (state == BUSY)
    {
        qDebug() << "The elevator came to the floor " << targetFloor;
        emit buttons_floor[targetFloor - 1]->unpressSignal();
        emit buttons_lift[targetFloor - 1]->unpressSignal();
        is_visit[targetFloor - 1] = false;


        if (identifyNewTarget(targetFloor))
            emit stopCabinSignal();
        else
        {
            state = FREE;
            emit stopCabinSignal();
        }
    }
}

void Controller::updateFloor()
{
    curFloor += direction;

     qDebug() << "The elevator goes to the floor " << curFloor;
}
