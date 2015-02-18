/*
Dylan Cooper
0839116
Assignment 1
June 5
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef COORD_H_DEF
#define COORD_H_DEF
#include "coordADT.h"
#endif



typedef struct List {
    Coordinate * value;
    struct List * next;
} node;

typedef struct ListHead {
    int length;
    struct List * next;   
} list;


list * createList();

node * getFirstNode(list * head);

void addFront(list * head, node * newNode);

void removeFromFront(list * head);

int listLength(list * head);

void printList(list * head, void (*formattedRecord)(char *, int, node *));

void destroyList(list * head);

node * init_node(Coordinate * coordinate);

void destroyNode(node * toDestroy);

Coordinate * getValue(node *);
