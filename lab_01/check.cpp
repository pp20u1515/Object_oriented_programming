#include "check.h"
#include "constants.h"
#include <string.h>

int checkCoordsEmpty(const pointsData_st &pointsData)
{
    int rc = OK; // код возврата

    if (pointsData.coords == nullptr) 
    {
        rc = ERR_EMPTY_MODEL;
    }

    return rc;
}


int checkEdgesEmpty(const edgesData_st &edgesData) 
{
    int rc = OK; // код возврата

    if (edgesData.edges == nullptr) 
    {
        rc = ERR_EMPTY_MODEL;
    }

    return rc;
}


int checkModelEmpty(const model_st &model) 
{
    int rc = OK; // код возврата

    if ((rc = checkCoordsEmpty(model.pointsData)) == OK)
    {
        rc = checkEdgesEmpty(model.edgesData);
    }

    return rc;
}


int checkCanvasEmpty(const canvas_st &canvas) 
{
    int rc = OK; // код возврата

    if (!canvas.scene) 
    {
        rc = ERR_EMPTY_SCENE;
    }

    return rc;
}


void handleError(const int &check, char error[])
{
    switch(check)
    {
        case (ERR_ALLOC_EDGES):
            strncpy(error, ERR_ALLOC_MSG, WORD_LEN);
            break;
        case (ERR_ALLOC_COORDS):
            strncpy(error, ERR_ALLOC_VERT_MSG, WORD_LEN);
            break;
        case (ERR_EMPTY_MODEL):
            strncpy(error, ERR_EMPTY_MODEL_MSG, WORD_LEN);
            break;
        case (ERR_FILE_READ_INT):
            strncpy(error, ERR_FILE_READ_INT_MSG, WORD_LEN);
            break;
        case (ERR_FILE_READ_POINT):
            strncpy(error, ERR_FILE_READ_POINT_MSG, WORD_LEN);
            break;
        case (ERR_FILE_READ_EDGE_CONNECTION):
            strncpy(error, ERR_FILE_READ_EDGE_MSG, WORD_LEN);
            break;
        case (ERR_SCALE_COEFF):
            strncpy(error, ERR_SCALE_COEFF_MSG, WORD_LEN);
            break;
        case (ERR_EMPTY_SCENE):
            strncpy(error, ERR_EMPTY_SCENE_MSG, WORD_LEN);
            break;
        default:
            break;
    } 
}
