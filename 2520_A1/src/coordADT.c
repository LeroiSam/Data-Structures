/*
Dylan Cooper
0839116
Assignment 1
June 5
*/

#include "coordADT.h"

#include <stdlib.h>

/*
init_coord(character-at-position, y-position, x-position) : created-coordinate
Post-conditions : Coordinate is initialized with allocated memory and input values.
*/

Coordinate * init_coord(char atPos, int yPos, int xPos){
    Coordinate * newCoord;          /*Coordinate being initialized*/

    newCoord = malloc(sizeof(Coordinate));

    newCoord->atPos = atPos;
    newCoord->yPos = yPos;
    newCoord->xPos = xPos;

    return newCoord;
}

/*
destroy_coord(to-destroy)
Post-conditions : All allocated memory for a coordinate is freed.
*/

void destroy_coord(Coordinate * toDestroy){
    free(toDestroy);
}


/*
getC(coordinate) : atPos
Post-conditions : returns the character at a value, \0 on error.
*/

char getC(Coordinate * coord){
    if (coord != NULL){
        return coord->atPos;
    }
    return '\0';
}


/*
getY(coordinate) : yPos
Post-conditions : returns the y position of the coordinate, -1 on error.
*/

int getY(Coordinate * coord){
    if (coord != NULL){
        return coord->yPos;
    }
    return -1;
}

/*
getX(coordinate) : xPos
Post-conditions : returns the x position of the coordinate, -1 on error.
*/

int getX(Coordinate * coord){
    if (coord != NULL){
        return coord->xPos;
    }
    return -1;
}