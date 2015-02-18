/*
Dylan Cooper
0839116
Assignment 1
June 5
*/

#include "maze.h"


/*
create_maze(file-name) : maze
Pre-conditions  : file-name contains a valid file with a maze file in it.
Post-conditions : maze is created and returned.
*/

maze * create_maze(char * fileName){
    maze * toCreate;            /*maze being created*/
    Coordinate * temp;          /*temporary variable to initialize coordinates*/

    char values[MAX_MAZE_SIZE+2][MAX_MAZE_SIZE+2];      /*2D array containing all the characters in the maze*/
    int maxY;                   /*number of rows*/
    int maxX;                   /*number of columns*/
    int i, j;                   /*control loops*/

    maxY = get_characters(fileName, values);
    maxX = strlen(values[0]);

    toCreate = malloc(sizeof(maze));

    for (i = 0; i < maxY; i++){
        for (j = 0; j < maxX; j++){
            temp = init_coord(values[i][j], i, j);
            toCreate->body[i][j] = temp;
            if (values[i][j] == 'S'){
                toCreate->startingPosition = temp;
            } else if (values[i][j] == 'F'){
                toCreate->finishingPosition = temp;
            }
        }
    }

    toCreate->rows = maxY;
    toCreate->cols = maxX;

    return toCreate;
}

/*
solve_maze(to-solve)
Pre-conditions  : maze is properly created using create_maze.
Post-conditions : maze is solved using a stack-based algorithm 
                  and the maze is changed to include the path.
*/

void solve_maze(maze * toSolve){
    Coordinate * currentPosition;   /*position at the start of each iteration*/
    Coordinate * nextPosition;      /*next position to move to*/
    stack * theStack;               /*the stack*/
    node * tempNode;                /*temporary node for popping off the stack*/
    int nextDirection;              /*direction to move in next*/

    theStack = create_stack();

    tempNode = init_node(toSolve->startingPosition);

    push(theStack, tempNode);

    while (getValue(peek(theStack)) != toSolve->finishingPosition){
        nextDirection = choose_next_direction(toSolve, theStack);
        currentPosition = getValue(peek(theStack));

        if (nextDirection != -1){
            /*Push next position to the stack*/
            nextPosition = go_forwards(toSolve, currentPosition, nextDirection);
            tempNode = init_node(nextPosition);
            push (theStack, tempNode);
        } else {
            /*Pop off stack and change dead end value to a character that will later be re-replaced with a space*/
            currentPosition->atPos = DEAD_END;
            tempNode = pop(theStack);
            destroyNode(tempNode);
        }
    }
    global_replace(toSolve, DEAD_END, ' ');

    destroy_stack(theStack);
}

/*
output_maze(to-output)
Pre-conditions  : to-output is properly created (starting and finishing positions aren't necessary).
Post-conditions : maze is printed to stdout.
*/

void output_maze(maze * toOutput){
    int i, j;       /*control loops*/

    for (i = 0; i < toOutput->rows; i++){
        for (j = 0; j < toOutput->cols; j++){
            putchar(toOutput->body[i][j]->atPos);
        }
        putchar('\n');
    }
}

/*
destroy_maze(to-destroy)
Pre-conditions  : to-destroy is either a NULL pointer or properly created.
Post-conditions : to-destroy is properly destroyed.
*/

void destroy_maze(maze * toDestroy){
    int i, j;       /*control loops*/

    if (toDestroy != NULL){
        for (i = 0; i < toDestroy->rows; i++){
            for (j = 0; j < toDestroy->cols; j++){
                destroy_coord(toDestroy->body[i][j]);
            }
        }
    }
    free(toDestroy);
}

/*
get_characters(file-name, maze-character-array) : number-of-rows
Pre-conditions  : valid file-name with a valid maze in it.
Post-conditions : maze-character-array is initialized with the maze from the file.
                  number of rows in the maze is returned.
*/

int get_characters(char * fileName, char values[MAX_MAZE_SIZE+2][MAX_MAZE_SIZE+2]){
    FILE * mazeFile;        /*file handle for maze file*/
    int i;                  /*controls loop*/

    mazeFile = fopen(fileName, "r");
    if (mazeFile == NULL){
        printf("The file could not be opened correctly.\n");
    }

    i = 0;
    while (fgets(values[i], MAX_MAZE_SIZE, mazeFile) != NULL && i < MAX_MAZE_SIZE){
        if (values[i][strlen(values[i]) - 1] == '\n'){
            values[i][strlen(values[i]) -1] = '\0';
        }
        i++;
    }
    fclose(mazeFile);

    return i;
}

/*
global_replace(maze, to-replace, to-replace-with)
Pre-conditions  : maze is initialized properly.
Post-conditions : all instances of to-replace in the maze are replaced with to-replace-with.
*/

void global_replace(maze * maze, int old, int new){
    int i, j;           /*control loops*/

    for (i = 0; i < maze->rows; i++){
        for (j = 0; j < maze->cols; j++){
            if (maze->body[i][j]->atPos == old){
                maze->body[i][j]->atPos = new;
            }
        }
    }
}

/*
choose_next_direction(maze, stack) : next-direction
Pre-conditions  : maze and stack are created properly, there is at least one coordinate pushed to the stack.
Post-conditions : returns the next direction to go (0 for up, 1 for left, 2 for down, 3 for right and -1 when 
                  there is nowhere to go (needs to be popped).
*/

int choose_next_direction(maze * maze, stack * stack){

    Coordinate * original;                  /*current position, where 'you' are moving from*/
    int curY, curX;                         /*current y and x positions*/

    original = getValue(peek(stack));
    curY = getY(original);
    curX = getX(original);

    if (is_char(maze, curY - 1, curX, ' ', 'F')){            /*up*/
        return 0;
    } else if (is_char(maze, curY, curX - 1, ' ', 'F')){     /*left*/
        return 1;
    } else if (is_char(maze, curY + 1, curX, ' ', 'F')){     /*down*/
        return 2;
    } else if (is_char(maze, curY, curX + 1, ' ', 'F')){     /*right*/
        return 3;
    }                                                        /*pop*/
    return -1;
}

/*
is_char(maze, yPos, xPos, first-check, second-check) : matches
Pre-conditions  : maze is properly initialized.
Post-conditions : returns whether or not the character 
                  of the maze at the position matches one of the two characters to check against.
*/

int is_char(maze * maze, int y, int x, char check1, char check2){
    if (y >= 0 && x >= 0 && y < maze->rows && x < maze->cols){
        return (getC(maze->body[y][x]) == check1 || getC(maze->body[y][x]) == check2);
    } else {
        return 0;
    }
}

/*
go_forwards(maze, current-position, direction) : new-position
Pre-conditions  : maze is initialized, current-position is valid.
Post-conditions : returns the coordinate for the new-position (moved one 
                  position from current-position in specified direction).
*/

Coordinate * go_forwards(maze * maze, Coordinate * currentPosition, int nextDirection){
    Coordinate * next;          /*coordinate being moved to*/
    int y, x;                   /*y and x positions*/

    y = getY(currentPosition);
    x = getX(currentPosition);

    currentPosition->atPos = PAST_MOVE;

    if (nextDirection == 0){            /*UP*/
        y--;
    } else if (nextDirection == 1){     /*LEFT*/
        x--;
    } else if (nextDirection == 2){     /*DOWN*/
        y++;
    } else if (nextDirection == 3){     /*RIGHT*/
        x++;
    }
    next = maze->body[y][x];

    return next;
}

