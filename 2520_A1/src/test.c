/*
Dylan Cooper
0839116
Assignment 1
June 5
*/

#include "test.h"

void formatCoordinate(char *, Coordinate *);

int main(){
    printf("PUSH, POP AND PEEK TESTS (CORRECT USAGE) :\n\n");
    pushPopPeekTest();
    printf("\n\nUNINITIALIZED VALUES IN FUNCTIONS (INCORRECT USAGE) :\n\n");
    uninitStackTest();
    return 0;
}


/********************************************
This function tests that the stack functions don't crash upon unexpected input
It tests how it reacts to an uninitialized stack, peeking and popping an empty
stack and trying to push an uninitialized value to a stack.
Results are to be checked by the user (by eye).  All invalid arguments are
handled correctly.
********************************************/
void uninitStackTest(){
    stack * newStack = NULL;        /*Stack to test with*/
    node * temp;                    /*temp variable used for pushing and popping values.*/
    Coordinate * sample;

    sample = init_coord('0', 0, 0);

    printf("\nFirst we'll try to push an initialized node to an uninitialized stack : \n");
    temp = init_node(sample);
    push(newStack, temp);
    destroy_coord(getValue(temp));
    destroyNode(temp);

    printf("\nNext, we'll try to pop off an uninitialized stack : \n");
    temp = pop(newStack);

    destroyNode(temp);

    printf("\nNext, we'll try to peek at an uninitialized stack : \n");
    temp = peek(newStack);

    printf("\nNext, we'll try to destroy an uninitialized stack : \n");
    printf("Note : There should be no error messages...\n");
    destroy_stack(newStack);

    newStack = create_stack();
    printf("\nNext, we'll try to pop from an initialized but empty stack : \n");
    temp = pop(newStack);
    destroyNode(temp);


    printf("\nNext, we'll try to peek from an initialized but empty stack : \n");
    temp = peek(newStack);

    printf("\nFinally, we'll try to push an uninitialized node to an initialized stack : \n");
    push(newStack, temp);
    
    destroy_stack(newStack);
}

/**********************************************
This function tests the stack functions with correct usage, making sure that they
do what they are expected to do.  It creates a stack, tests it with push, pop and 
peek, and destroys it.  All of the functions work correctly.
**********************************************/

void pushPopPeekTest(){
    stack * newStack = create_stack();      /*Stack being manipulated*/
    node * temp;                            /*Used to pop values*/
    int i;                                  /*Controls Loop*/
    Coordinate * poppedValue;               /*Value popped from the stack*/
    Coordinate ** sampleCoordinates;     /*Array of coordinates being added to stack*/
    char * stringForFormatting;

    sampleCoordinates = malloc(sizeof(Coordinate *) * 10);

    stringForFormatting = malloc(sizeof(char) * 50);
    
    printf("Initializing the stack...\n");

    for (i = 0; i < 10; i++){
        sampleCoordinates[i] = init_coord('A' + i, i, i);
    }
    for (i = 9; i >= 0; i--){
        push(newStack, init_node(sampleCoordinates[i]));
    }
    
    temp = pop(newStack);
    poppedValue = getValue(temp);
    destroyNode(temp);
    
    formatCoordinate(stringForFormatting, poppedValue);

    printf("By popping, we can expect 0, 0, A, and we find : %s\n", stringForFormatting);
    printf("And, we can push the value back on!\n");
    
    push(newStack, init_node(poppedValue));
    
    formatCoordinate(stringForFormatting, getValue(peek(newStack)));
    printf("By peeking, we expect the same as above, we find : %s\n", stringForFormatting);
    printf("Now, let's pop a few (4) more off!\n");
    
    for (i = 0; i < 4; i++){
        temp = pop(newStack);
        destroyNode(temp);
    }

    formatCoordinate(stringForFormatting, getValue(peek(newStack)));
    printf("Now when we peek, we can expect 4, 4, E, and we find : %s\n", stringForFormatting);

    destroy_stack(newStack);

    for (i = 0; i < 10; i++){
        destroy_coord(sampleCoordinates[i]);
    }
    free(sampleCoordinates);
    free(stringForFormatting);
}

void formatCoordinate(char * string, Coordinate * toFormat){
    sprintf(string, "\nY:%d\tX:%d\tValue:%c\n", getY(toFormat), getX(toFormat), getC(toFormat));
}