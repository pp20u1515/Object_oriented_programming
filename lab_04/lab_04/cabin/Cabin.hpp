#ifndef CABIN_HPP
#define CABIN_HPP

#include <QObject>
#include <QTimer>

#include "doors/Doors.hpp"

class Cabin : public QObject
{
    Q_OBJECT

    using cabinState = enum {
        WAIT,
        MOVING,
        STOP
    };

public:
    explicit Cabin(QObject *parent = nullptr);
    ~Cabin() override = default;

signals:
    void openDoors();
    void updateFloorSignal();
    void readyToMoveSignal();
    void cabinFinished(bool, int=1);

public slots:
    void stopCabin();
    void moveCabin();
    void free();

private:
    cabinState state;
    Doors doors;
    QTimer moveTimer;
};


#endif // CABIN_HPP
