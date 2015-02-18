#include "listPlus.h"

/*
*Recursive Function*
Pre-conditions  : list is a sorted list, toAdd is an initialized node
                  pos is the position to start search (0 to start),
                  len is the length of the list, compare function 
                  should take two nodes.
Post-conditions : adds the node to the list in appropriate place, 
                  returns 1 on error(node already in list), 0 on 
                  success.
Complexity      : O(n log(n))
                  getElement is O(n), algorithm is O(log(n))
*/

int add_to_sorted_list(list * list, node * toAdd, unsigned pos, unsigned len, int (*compar)(const void *, const void *)){
    if (len <= 1){
        list->length++;
        if (pos == 0){
            addFront(list, toAdd);
        } else {
            node * temp = getElement(list, pos);
            toAdd->next = temp->next;
            temp->next = toAdd;
        }
    } else {
        node * toCmpr = getElement(list, pos + CEIL(len, 2));
        if (compar(toAdd, toCmpr) == 0){
            return 1;
        } else if (compar(toAdd, toCmpr) < 0){
            return add_to_sorted_list(list, toAdd, pos, CEIL(len, 2), compar);
        } else {
            return add_to_sorted_list(list, toAdd, pos + CEIL(len, 2), CEIL(len, 2), compar);
        }
    }
    return 0;
}

/*
Pre-conditions  : list is a sorted list, key is an initialized string,
                  pos is the position to start search (0 to start),
                  len is the length of the list, compare function 
                  should take a string first and a node second.
Post-conditions : returns the node with the appropriate key, NULL when
                  it can't be found.
Complexity      : O(n log(n))
                  getElement is O(n), algorithm is O(log(n))
*/
node * look_through_sorted_list(list * list, char * key, unsigned pos, unsigned len, int (*compar)(const void *, const void *)){
    if (len == 0){
        fprintf(stderr, "Error : Key Not Found\n");
        return NULL;
    } else if (len == 1){
        return getElement(list, pos);
    } else {
        node * toCmpr = getElement(list, pos + CEIL(len, 2));

        if (compar(key, toCmpr) < 0){
            return look_through_sorted_list(list, key, pos, CEIL(len, 2), compar);
        } else {
            return look_through_sorted_list(list, key, pos + CEIL(len, 2), CEIL(len, 2), compar);
        }
    }
}

/*
Pre-conditions  : list is initialized.
Post-conditions : returns correct node; NULL if list is NULL or 
                  position is 0 and the last node if the position
                  is past the length of the list.
*/
node * getElement(list * list, unsigned position){
    if (position == 0 || list == NULL){
        return NULL;
    } else {
        node * iterator = list->next;
        int i;
        for (i = 1; i < position && iterator->next != NULL ; i++){
            iterator = iterator->next;
        }
        return iterator;
    }
}


/*
Description     : Makes comparison of phone numbers from two nodes.
*/
int listing_compare(void const *a, void const *b) { 
    node *aa = (node *)a;
    node *bb = (node *)b;
    return strcmp(getValue(aa)->phone, getValue(bb)->phone);
}

/*
Description     : Makes comparison of phone numbers from a string 
                  and a node (string first).
*/
int key_compare(void const * a, void const * b){
    char * aa = (char *)a;
    node * bb = (node *)b;
    return strcmp(aa, getValue(bb)->phone);
}

/*
Description     : Does a full alphabetical comparison of string
                  listing in format LASTNAMEFIRSTNAMEPHONENUMBER.
*/

int name_compare(void const * a, void const * b){
    node * aa = (node *)a;
    node * bb = (node *)b;
    Listing * listingA = getValue(aa);
    Listing * listingB = getValue(bb);
    char stringA[51] = "";
    char stringB[51] = "";

    strcat(stringA, listingA->last);
    strcat(stringA, listingA->first);
    strcat(stringA, listingA->phone);
    strcat(stringB, listingB->last);
    strcat(stringB, listingB->first);
    strcat(stringB, listingB->phone);
    
    return strcmp(stringA, stringB);
}