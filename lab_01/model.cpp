#include <stdlib.h>

#include "model.h"
#include "constants.h"
#include "check.h"
#include "draw.h"
#include "edges.h"
#include "edge.h"
#include "point.h"
#include "points.h"

model_st &initModel()
{
    static model_st model;

    model.pointsData.coords = nullptr;
    model.edgesData.edges = nullptr;

    return model;
}

void freeModel(model_st &model)
{
    freeEdges(model.edgesData);
    freePoints(model.pointsData.coords);
}

int loadTempModel(model_st &tempModel, FILE *file)
{
    int rc = readPoint(tempModel.center, file);

    if (rc == OK)
    {
        rc = loadPoints(tempModel.pointsData, file);

        if (rc == OK)
        {
            rc = loadEdges(tempModel.edgesData, file);

            if (rc != OK)
                freePoints(tempModel.pointsData.coords);
        }
    }

    return rc;
}

int loadModel(model_st &model, const char fileName[]) 
{
    FILE *file = fopen(fileName, "r");
    int rc = OK; // код возврата

    if (!file)
        rc = ERR_OPEN_FILE;
    else
    {
        model_st tempModel = initModel();
        rc = loadTempModel(tempModel, file);
        fclose(file);

        if (rc == OK)
        {
            freeModel(model);
            model = tempModel;
        }
    }

    return rc;
}

int scaleModel(model_st &model, const scale_st &scale) 
{
    int rc = checkModelEmpty(model); // код возврата

    if (rc == OK)
    {
        scalePoints(model.pointsData, scale, model.center);
    }

    return rc;
}

int moveModel(model_st &model, const move_st &move) 
{
    int rc = checkModelEmpty(model);

    if (rc == OK)
    {
        movePoints(model.pointsData, move);
        movePoint(model.center, move);
    }

    return rc;
}

int rotateModel(model_st &model, const rotate_st &rotate) 
{
    int rc = checkModelEmpty(model);

    if (rc == OK)
    {
        rotatePoints(model.pointsData, rotate, model.center);
    }

    return rc;
}

int drawModel(const model_st &model, const canvas_st &canvas) 
{
    int rc = checkModelEmpty(model);

    if (rc == OK)
    {
        rc = checkCanvasEmpty(canvas);

        if (rc == OK)
        {
            prepareCanvas(canvas);
            rc = drawEdges(model.edgesData, model.pointsData, canvas);
        }
    }

    return rc;
}
