#include "draw_qt.h"

void prepareCanvas(const canvas_st &canvas)
{
    canvas.scene->clear();
}

void drawLine(const point_st &point1, const point_st &point2, const canvas_st &canvas) 
{
    canvas.scene->addLine(point1.x, point1.y, point2.x, point2.y);
}
