#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <memory>
#include <vector>

#include "defines.hpp"
#include "button/Button.hpp"

class Controller : public QWidget
{
    Q_OBJECT

    using ControllerState = enum
    {
        FREE,
        BUSY
    };

public:
    explicit Controller(QWidget *parent = nullptr);
    ~Controller() override = default;

signals:
    void stopCabinSignal();
    void moveCabinSignal();
    void reachFloorSignal();

public slots:
    void newTarget(bool ,int = 1);
    void reachFloor();

private:
    bool identifyNewTarget(int &new_target);
    void decideDirection();
    void updateFloor();

private:
    int curFloor = START_FLOOR;
    int targetFloor = START_FLOOR;

    Direction last_direction = STAY;
    Direction direction = STAY;

    ControllerState state = FREE;
    std::vector<bool> is_visit;

    std::vector<std::shared_ptr<Button>> buttons_floor;
    std::vector<std::shared_ptr<Button>> buttons_lift;
    std::unique_ptr<QVBoxLayout> layout;
};

#endif //CONTROLLER_HPP
