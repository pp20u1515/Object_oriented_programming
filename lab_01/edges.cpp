#include "edges.h"
#include "edge.h"
#include "constants.h"

void freeEdges(edgesData_st &edgesData) 
{
    if (edgesData.edges != nullptr)
    {
        delete[] edgesData.edges;
    }
}

int allocateEdges(edgesData_st &edgesData) 
{
    edgesData.edges = new edgeT[edgesData.edges_count];
    int rc = OK; // код возврата

    if (edgesData.edges == nullptr) 
    {
        rc = ERR_ALLOC_EDGES;
    }

    return rc;
}

int readEdges(edgesData_st &edgesData, FILE *file) 
{
    int rc = OK; // код возврата

    for (int i = 0; rc == OK && i < edgesData.edges_count; i++)
    {
        rc = readEdge(edgesData.edges[i], file);
    }

    return rc;
}

int loadEdges(edgesData_st &edgesData, FILE *file) 
{
    int rc = readAmount(edgesData, file);

    if (rc == OK)
    {
        rc = allocateEdges(edgesData);

        if (rc == OK)
        {
            rc = readEdges(edgesData, file);

            if (rc != OK)
                freeEdges(edgesData);
        }
    }

    return rc;
}
