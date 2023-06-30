#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QGraphicsScene>

typedef struct
{
    double kx;
    double ky;
    double kz;
} scale_st;


typedef struct 
{
    double dx;
    double dy;
    double dz;
} move_st;


typedef struct 
{
    double angle_x;
    double angle_y;
    double angle_z;
} rotate_st;


typedef struct
{
    QGraphicsScene *scene;
} canvas_st;

#endif // STRUCTURES_H