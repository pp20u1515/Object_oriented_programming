#include "edge.h"
#include "constants.h"

int readAmount(edgesData_st &edgesData, FILE *file) 
{
    int rc = OK; // код возврата

    if (fscanf(file, "%d", &edgesData.edges_count) != 1) 
    {
        rc = ERR_FILE_READ_EDGE_COUNT;
    }

    return rc;
}

int readEdge(edgeT &edge, FILE *file) 
{
    int rc = OK; // код возврата

    if (fscanf(file, "%d%d", &edge.left_vertex, &edge.right_vertex) != 2) 
    {
        rc = ERR_FILE_READ_EDGE_CONNECTION;
    }

    return rc;
}