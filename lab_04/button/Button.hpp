#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <QPushButton>
#include <memory>

class Button : public QPushButton
{
    Q_OBJECT;

    using ButtonState = enum
    {
        ACTIVE,
        NOT_ACTIVE
    };

public:
    explicit Button(QWidget *parent = nullptr);
    ~Button() override = default;

    void setFloor(int floor);

signals:
    void pressSignal(bool, int);
    void unpressSignal();

public slots:
    void pressSlot();
    void unpressSlot();

private:
    ButtonState state;
    size_t currentButtonFloor;
};

#endif // BUTTON_HPP
