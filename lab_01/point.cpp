#include "math.h"
#include "point.h"
#include "constants.h"
#include "utils.h"

void scalePoint(point_st &point, const scale_st &scale, const point_st &center)
{
    point.x = ((point.x - center.x) * scale.kx) + center.x;
    point.y = ((point.y - center.y) * scale.ky) + center.y;
    point.z = ((point.z - center.z) * scale.kz) + center.z;
}

void movePoint(point_st &point, const move_st &move)
{
    point.x += move.dx;
    point.y += move.dy;
    point.z += move.dz;
}

void addCenter(point_st &point, const point_st &center)
{
    point.x += center.x;
    point.y += center.y;
    point.z += center.z;
}

void subtractCenter(point_st &point, const point_st &center)
{
    point.x -= center.x;
    point.y -= center.y;
    point.z -= center.z;
}

void rotatePoint(point_st &point, const rotate_st &rotate, const point_st &center)
{
    subtractCenter(point, center);

    if (fabs(rotate.angle_x) > EPS) 
    {
        rotatePointX(point, rotate.angle_x);
    }
    else if (fabs(rotate.angle_y) > EPS) 
    {
        rotatePointY(point, rotate.angle_y);
    }
    else if (fabs(rotate.angle_z) > EPS) 
    {
        rotatePointZ(point, rotate.angle_z);
    }

    addCenter(point, center);
}

void rotatePointX(point_st &point, const double &angle)
{
    double cosA = getCosAngle(angle);
    double sinA = getSinAngle(angle);
    double tempY = point.y;

    point.y = point.y * cosA - point.z * sinA;
    point.z = tempY * sinA + point.z * cosA;
}

void rotatePointY(point_st &point, const double &angle)
{
    double cosA = getCosAngle(angle);
    double sinA = getSinAngle(angle);
    double tempX = point.x;

    point.x = point.x * cosA + point.z * sinA;
    point.z = -tempX * sinA + point.z * cosA;
}

void rotatePointZ(point_st &point, const double &angle)
{
    double cosA = getCosAngle(angle);
    double sinA = getSinAngle(angle);
    double tempX = point.x;

    point.x = point.x * cosA - point.y * sinA;
    point.y = tempX * sinA + point.y * cosA;
}

int readAmount(int &vertices_count, FILE *file)
{
    int rc = OK; // код возврата

    if (fscanf(file, "%d", &vertices_count) != 1)
    {
        rc = ERR_FILE_READ_VERTICES_COUNT;
    }

    return rc;
}

int readPoint(point_st &point, FILE *file)
{
    int rc = OK; // код возврата

    if (fscanf(file, "%lf%lf%lf", &point.x, &point.y, &point.z) != 3)
    {
        rc = ERR_FILE_READ_POINT;
    }

    return rc;
}
