#include "draw.h"
#include "constants.h"

point_st getPoint(const point_st coords[], const int &index) 
{
    return coords[index];
}

int drawEdge(const edgeT &edge, const point_st coords[], const canvas_st &canvas)
{
    int rc = OK;
    point_st point1 = getPoint(coords, edge.left_vertex); // проверки

    if (point1.x && point1.y && point1.z)
    {
        point_st point2 = getPoint(coords, edge.right_vertex);

        if (point2.x && point2.y && point2.z)
            drawLine(point1, point2, canvas);
        else
            rc = ERR_EMPTY_DATA;
    }
    else
        rc = ERR_EMPTY_DATA;
    return rc;
}

int drawEdges(const edgesData_st &edgesData, const pointsData_st &pointsData, const canvas_st &canvas)
{
    int rc = OK;

    for (int i = 0; rc == OK && i < edgesData.edges_count; i++)
    {
        rc = drawEdge(edgesData.edges[i], pointsData.coords, canvas);
    }
    return rc;
}
