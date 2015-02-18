/*
Dylan Cooper
0839116
Assignment 1
June 5
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"


#ifndef COORD_H_DEF
#define COORD_H_DEF
#include "coordADT.h"
#endif

#define PAST_MOVE 'X'
#define DEAD_END '@'
#define MAX_MAZE_SIZE 105


typedef struct Maze{
    Coordinate * body[MAX_MAZE_SIZE][MAX_MAZE_SIZE];
    int rows;                                           /*Y*/
    int cols;                                           /*X*/
    Coordinate * startingPosition;
    Coordinate * finishingPosition;
} maze;

maze * create_maze(char *);

void output_maze(maze *);

void solve_maze(maze *);

void destroy_maze(maze *);

int get_characters(char *, char [MAX_MAZE_SIZE+2][MAX_MAZE_SIZE+2]);

int choose_next_direction(maze * maze, stack * stack);

int is_char(maze *, int, int, char, char);

Coordinate * go_forwards(maze *, Coordinate *, int);

void global_replace(maze *, int, int);
