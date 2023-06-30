#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
    int left_vertex;
    int right_vertex;
} edgeT;


typedef struct 
{
    edgeT *edges;
    int edges_count;
} edgesData_st;

int readEdge(edgeT &edge, FILE *file);

int readAmount(edgesData_st &edgesData, FILE *file);

#endif // EDGE_H