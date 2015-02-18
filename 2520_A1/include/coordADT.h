/*
Dylan Cooper
0839116
Assignment 1
June 5
*/

typedef struct CoordinateInfo{
    char atPos;
    int yPos;
    int xPos;
} Coordinate;

Coordinate * init_coord(char, int, int);
void destroy_coord(Coordinate *);
char getC(Coordinate *);
int getY(Coordinate *);
int getX(Coordinate *);
