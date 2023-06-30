#include "utils.h"
#include "math.h"

double getCosAngle(const double &angle)
{
    return cos(angle * M_PI / 180);
}

double getSinAngle(const double &angle)
{
    return sin(angle * M_PI / 180);
}
