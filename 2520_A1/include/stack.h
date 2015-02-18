/*
Dylan Cooper
0839116
Assignment 1
June 5
*/

#ifndef LIST_H_DEF
#define LIST_H_DEF
#include "list.h"
#endif

struct StackType {
    list * list;
};

typedef struct StackType stack;


stack * create_stack();

void destroy_stack(stack *);

void push(stack *, node *);

node * pop(stack *);

node * peek(stack *);

int is_empty(stack *);