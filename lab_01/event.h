#ifndef EVENT_H
#define EVENT_H

#include <QGraphicsScene>
#include "structures.h"
#include "constants.h"

typedef struct 
{
    int type;

    union 
    {
        char fileName[FILE_NAME_LEN];
        canvas_st canvas;
        scale_st scale;
        rotate_st rotate;
        move_st move;
    };
} event_st;

int eventHandler(const event_st &event);

#endif // EVENT_H
