#ifndef DRAW_QT_H
#define DRAW_QT_H

#include "structures.h"
#include "point.h"

void prepareCanvas(const canvas_st &canvas);

void drawLine(const point_st &point1, const point_st &point2, const canvas_st &canvas);

#endif // DRAW_QT_H
