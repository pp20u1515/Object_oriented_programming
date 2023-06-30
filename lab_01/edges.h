#ifndef EDGES_H
#define EDGES_H

#include <stdlib.h>
#include <stdio.h>
#include "edge.h"

void freeEdges(edgesData_st &edgesData);

int allocateEdges(edgesData_st &edgesData);

int loadEdges(edgesData_st &edgesData, FILE *file);

int readEdges(edgesData_st &edgesData, FILE *file);

#endif // EDGES_H