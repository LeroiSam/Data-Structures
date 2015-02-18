/*
Dylan Cooper
0839116
Assignment 1
June 5
*/

#include <stdio.h>
#include <stdlib.h>
#include "listCustom.h"



typedef struct List {
    ListElement * value;
    struct List * next;
} node;

typedef struct ListHead {
    int length;
    struct List * next;   
} list;


list * createList();

node * getFirstNode(list * head);

void addFront(list * head, node * newNode);

void removeFromFront(list * head, void (*destroy_contents)(ListElement *));

int listLength(list * head);

void printList(list * head, void (*formattedRecord)(char *, int, node *));

void destroyList(list * head, void (*destroy_contents)(ListElement *));

node * init_node(ListElement * element);

void destroyNode(node * toDestroy, void (*destroy_contents)(ListElement *));

ListElement * getValue(node *);
