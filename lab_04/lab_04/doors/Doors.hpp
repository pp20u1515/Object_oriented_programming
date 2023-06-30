#ifndef DOORS_HPP
#define DOORS_HPP

#include <QObject>
#include <QTimer>

class Doors : public QObject
{
    Q_OBJECT

    using doorsState = enum {
        OPEN,
        CLOSED,
        OPENING,
        CLOSING
    };

public:
    Doors();
    ~Doors() override = default;

signals:
    void doorClosed();

private slots:
    void startClosing();
    void startOpening();

public slots:
    void open();
    void close();

private:
    doorsState state;

    QTimer openTimer;
    QTimer closeTimer;
    QTimer waitTimer;
};


#endif //DOORS_HPP
