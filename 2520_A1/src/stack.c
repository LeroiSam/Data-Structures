/*
Dylan Cooper
0839116
Assignment 1
June 5
*/

#include "stack.h"


/*****************************************
create_stack(): stack
Preconditions : No preconditions.
Postconditions : Returns a pointer to a stack with newly allocated memory.
*****************************************/
stack * create_stack(){
    stack * new = malloc(sizeof(stack));
    new->list = createList();
    return new;
}

/****************************************
destroy_stack(stack)
Preconditions : Send in pointer to a created stack.  
Postconditions : All memory allocated for the stack is freed.
Note : if no memory is allocated, this does not raise an error.
****************************************/
void destroy_stack(stack * toDestroy){
    if (toDestroy != NULL){
        destroyList(toDestroy->list);
        free(toDestroy);
    }
}

/****************************************
push(stack, new-node)
Preconditions : stack is initialized correctly (using create_stack)
                and new-node is initialized (using initializeNode).
Postconditions : new-node is pushed onto the top of the stack.
                 Prints to stderr on error.
****************************************/

void push(stack * stack, node * newElement){
    if (stack == NULL){
        fprintf(stderr, "The stack must be created before pushing.\n");
    } else if (newElement == NULL){
        fprintf(stderr, "The element to be pushed to the stack was not correctly initialized.\n");
    } else {
        addFront(stack->list, newElement);
    }
}

/****************************************
pop(stack) : former-top
Preconditions : stack is initialized correctly (using create_stack)
                and has at least one element.
Postconditions : takes the top element off the stack and returns a
                 pointer to that element.
Note for usage : the returned value will be in allocated memory, it
                 needs to be freed using destroyNode() after being popped.
****************************************/

node * pop(stack * stack){
    node * new;
    if (stack == NULL || stack->list == NULL){
        fprintf(stderr, "The stack must be created before popping.\n");
        new = NULL;
    } else {
        new = init_node(getValue(getFirstNode(stack->list)));
        removeFromFront(stack->list);
    }
    return new;
}

/************************************
peek(stack) : top
Preconditions : stack is initialized correctly (using create_stack)
                and has at least one element.
Postconditions : Returns the top element off the stack.
************************************/

node * peek(stack * stack){
    if (stack == NULL || stack->list == NULL){
        fprintf(stderr, "The stack must be created before peeking.\n");
        return NULL;
    } else {
        return getFirstNode(stack->list);
    }
}

int is_empty(stack * stack){
    if (stack->list->length == 0){
        return 1;
    } else {
        return 0;
    }
}