/*
Dylan Cooper
0839116
Assignment 1
June 5
*/

#include "list.h"

/*************************************************
createList()
returns the head of an empty list
*************************************************/

list * createList() {
    list * head = malloc(sizeof(node));
    head->length = 0;
    head->next = NULL;
    return head;
}

/*************************************************
getFirstNode(head-of-list) : node
Takes the head of the list and returns the first node in the list.
*************************************************/

node * getFirstNode(list * head){
    if (head == NULL){
        fprintf(stderr, "The list must be created before getting the first node.\n");
        return NULL;
    } else if (head->next == NULL) {
        fprintf(stderr, "The list is empty, can't get the first node\n");
        return NULL;
    } else {
        return head->next;
    }
}

/*************************************************
addFront(head-of-list, node-to-add)
Preconditions : head-of-list has been created
                node-to-add has been initialized
Postconditions : node-to-add is in first position of list
                 outputs to stderr on error
*************************************************/

void addFront(list * head, node * newNode)
{
    if (head == NULL){
        fprintf(stderr, "The list must be created before adding to front.\n");
    } else if (newNode == NULL){
        fprintf(stderr, "The node trying to be added needs to be initialized first.\n");
    } else {
        head->length++;
        newNode->next = head->next;
        head->next = newNode;
    }
}

/*************************************************
removeFromFront(head-of-list, void-function-pointer-destroy(node *))
Preconditions : head-of-list has been created.
Postconditions : First element of list is removed, and destroyed.
                 Prints to stderr on error.
*************************************************/

void removeFromFront(list * head)
{
    node * temp;
    if (head == NULL) {
        fprintf(stderr, "The list must be created before removing from front.\n");
    } else if (head->next == NULL) {
        fprintf(stderr, "The list has no elements to remove.\n");
    } else {
        head->length--;
        temp = head->next;
        head->next = head->next->next;
        destroyNode(temp);
    }
}

/*************************************************
listLength(head-of-list) : int
Preconditions : head-of-list has been created.
Postconditions : Returns the number of elements in the list.
                 Writes to stderr and returns -1 on error.
*************************************************/

int listLength(list * head){
    int length = 0;
    if (head == NULL){
        fprintf(stderr, "The list must be created before finding its length.\n");
        length = -1;
    } else {
        length = head->length;
    }
    return length;
}

/*************************************************
printList(head-of-list, void-function-pointer-format(char *, int, node *))
Preconditions : head-of-list has been created.
                format function properly points to a function that will format the struct into a string for output.
                More documentation on function in README.txt
Postconditions : No changes in list or variables, this function just prints the list in the specified format.
*************************************************/

void printList(list * head, void (*formatRecord)(char *, int, node *))
{
    int count = 0;
    node * current;
    char * formattedString = malloc(sizeof(char) * 200);

    if (head == NULL){
        fprintf(stderr, "The list must be created before printing it.\n");
    } else {
        current = head->next;
        while (current != NULL)
        {
            formatRecord(formattedString, count, current);
            printf("%s", formattedString);
            count++;
            current = current->next;
        }
    }
    free(formattedString);
}

/*************************************************
destroyList(head-of-list)
Preconditions : head-of-list has been created.
Postconditions : list is destroyed, all elements are destroyed based on destroyNode.
*************************************************/

void destroyList(list * head)
{
    node * currentRecord;
    node * nextRecord;
    nextRecord = head->next;
    while (nextRecord != NULL)
    {
        currentRecord = nextRecord;
        nextRecord = currentRecord->next;
        destroyNode(currentRecord);
    }
    free(head);
}

/*************************************************
initializeNode(integer-value) : node *
Preconditions : integer-value is a valid integer to be stored in the list.
Postconditions : returns a node with integer-value as it's value, next is NULL.
*************************************************/

node * init_node(Coordinate * temp){
    node * newNode = malloc(sizeof(node));
    newNode->value = temp;
    newNode->next = NULL;
    return newNode;
}

/*************************************************
destroyNode(node-to-destroy)
Preconditions : node-to-destroy is pointing at allocated memory.
Postconditions : node-to-destroy is destroyed.
Note : toDestroy->value is not freed because it is meant for the 
       user of the ADT to keep track of it themselves. 
*************************************************/

void destroyNode(node * toDelete){
    free(toDelete);
}

/*************************************************
getValue(node) : int
Preconditions : node contains an initialized node.
Postconditions : returns the value contained in the node.
*************************************************/
Coordinate * getValue(node * temp){
    if (temp == NULL){
        fprintf(stderr, "The node must be initialized before the value is found.\n");
        return 0;
    } else {
        return temp->value;
    }
}