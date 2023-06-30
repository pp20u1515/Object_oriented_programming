#ifndef POINT_H
#define POINT_H

#include "structures.h"

typedef struct 
{
    double x;
    double y;
    double z;
} point_st;

typedef struct
{
    point_st *coords;
    int vertices_count;
} pointsData_st;

void scalePoint(point_st &point, const scale_st &scale_coeff,  const point_st &center);

void rotatePoint(point_st &point, const rotate_st &angle, const point_st &center);

void subtractCenter(point_st &point, const point_st &center);

void addCenter(point_st &point, const point_st &center);

void rotatePointX(point_st &point, const double &angle);

void rotatePointZ(point_st &point, const double &angle);

void rotatePointY(point_st &point, const double &angle);

void movePoint(point_st &point, const move_st &move);

int readPoint(point_st &point, FILE *file);

int readAmount(int &vertices_count, FILE *file);

#endif // POINT_H
