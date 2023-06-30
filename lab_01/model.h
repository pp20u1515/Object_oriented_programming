#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include "structures.h"
#include "point.h"
#include "edge.h"

typedef struct 
{
    pointsData_st pointsData;
    edgesData_st edgesData;
    point_st center;
} model_st;

model_st &initModel();

void freeModel(model_st &model);

int loadModel(model_st &model, const char fileName[]);

int scaleModel(model_st &model, const scale_st &scale);

int moveModel(model_st &model, const move_st &move);

int rotateModel(model_st &model, const rotate_st &rotate);

int drawModel(const model_st& model, const canvas_st &canvas);

#endif // MODEL_H
