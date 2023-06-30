#ifndef LIFT_HPP
#define LIFT_HPP

#include <QObject>

#include "controller/Controller.hpp"
#include "cabin/Cabin.hpp"

class Lift : public QObject
{
    Q_OBJECT

public:
    explicit Lift(QObject *parent = nullptr);
    ~Lift() = default;

    QWidget* widget();

private:
    Controller controller;
    Cabin cabin;
};


#endif //LIFT_HPP
