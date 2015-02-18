/*
Dylan Cooper
0839116
Assignment 1
June 5
*/

#include "main.h"

int main(int argc, char * argv[]){

    maze * maze;        /*maze being solved*/

    if (argc != 2){
        printf("Incorrect Usage: send input file as command line argument.\n");
        return 1;
    }
    maze = create_maze(argv[1]);

    if (maze == NULL){
        printf("Error creating the maze.\n");
        return 1;
    }

    solve_maze(maze);

    output_maze(maze);

    destroy_maze(maze);

    return 0;
}
