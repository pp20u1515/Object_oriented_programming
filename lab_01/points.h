#ifndef POINTS_H
#define POINTS_H

#include "structures.h"
#include "point.h"

void scalePoints(pointsData_st &pointsData, const scale_st &scale, const point_st &center);

void movePoints(pointsData_st &pointsData, const move_st &move);

void rotatePoints(pointsData_st &pointsData, const rotate_st &rotate, const point_st &center);

//void freePoints(pointsData_st &pointsData);
void freePoints(point_st pointsData[]);

//int allocatePoints(pointsData_st &pointsData);
int allocatePoints(point_st pointsData[], const int vertices_count);

int loadPoints(pointsData_st &pointsData, FILE *file);

int readAmount(pointsData_st &pointsData, FILE *file);

#endif // POINTS_H
