#include <stdlib.h>
#include "event.h"
#include "constants.h"
#include "model.h"

// начало программы
int eventHandler(const event_st &event)
{
    int rc = OK; // код возврата
    static model_st model = initModel();

    switch(event.type)
    {
        case (LOAD_MODEL):
            rc = loadModel(model, event.fileName);;
            break;
        case (DRAW_MODEL):
            rc = drawModel(model, event.canvas);
            break;
        case (MOVE_MODEL):
            rc = moveModel(model, event.move);
            break;
        case (ROTATE_MODEL):
            rc = rotateModel(model, event.rotate);
            break;
        case (SCALE_MODEL):
            rc = scaleModel(model, event.scale);
            break;
        case (FREE_MODEL):
            freeModel(model);
            break;
        default:
            rc = ERR_UNKNOWN_COMMAND;
    }

    return rc;
}
