#ifndef DRAW_H
#define DRAW_H

#include "draw_qt.h"
#include "model.h"

void drawLine(const point_st &point1, const point_st &point2, const canvas_st &canvas);

int drawEdges(const edgesData_st &edgesData, const pointsData_st &pointsData, const canvas_st &canvas);


#endif // DRAW_H
