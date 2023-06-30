#include "point.h"
#include "math.h"
#include "points.h"
#include "point.h"
#include "constants.h"

void movePoints(pointsData_st &pointsData, const move_st &move)
{
    for (int i = 0; i < pointsData.vertices_count; i++) 
    {
        movePoint(pointsData.coords[i], move);
    }
}

void rotatePoints(pointsData_st &pointsData, const rotate_st &rotate, const point_st &center)
{
    for (int i = 0; i < pointsData.vertices_count; i++)
    {
        rotatePoint(pointsData.coords[i], rotate, center);
    }
}

void scalePoints(pointsData_st &pointsData, const scale_st &scale, const point_st &center)
{
    for (int i = 0; i < pointsData.vertices_count; i++) 
    {
        scalePoint(pointsData.coords[i], scale, center);
    }
}

int readPoints(point_st pointsData[], const int vertices_count, FILE *file)
{
    int rc = OK; // код возврата

    for (int i = 0; rc == OK && i < vertices_count; i++)
    {
       rc = readPoint(pointsData[i], file);
    }

    return rc;
}

int loadPoints(pointsData_st &pointsData, FILE *file)
{
    int rc = readAmount(pointsData.vertices_count, file);

    if (rc == OK)
    {
        rc = allocatePoints(pointsData.coords, pointsData.vertices_count);

        if (rc == OK)
        {
            rc = readPoints(pointsData.coords, pointsData.vertices_count, file);

            if (rc != OK)
                freePoints(pointsData.coords);
        }
    }

    return rc;
}

void freePoints(point_st pointsData[])
{
    if (pointsData != nullptr)
    {
        delete[] pointsData;
    }
}

int allocatePoints(point_st pointsData[], const int vertices_count)
{
    pointsData = new point_st[vertices_count];
    int rc = OK; // код возврата

    if (pointsData == nullptr)
    {
        rc = ERR_ALLOC_COORDS;
    }

    return rc;
}
