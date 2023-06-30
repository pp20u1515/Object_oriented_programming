#ifndef CHECK_H
#define CHECK_H

#include "model.h"

int checkModelEmpty(const model_st &model);

int checkCanvasEmpty(const canvas_st &canvas);

void handleError(const int &check, char error[]);

#endif // CHECK_H
