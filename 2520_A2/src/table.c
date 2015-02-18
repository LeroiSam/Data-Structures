#include "table.h"

/*
Post-conditions : Returns a properly created hash table.
*/
Table * ht_create(unsigned tableSize){
    Table * new;        /*new table being created*/
    int i;              /*controls loop*/

    new = malloc(sizeof(Table));

    new->size = tableSize;
    new->fullList = createList();
    new->body = malloc(sizeof(list *) * tableSize);
    for (i = 0; i < tableSize; i++){
        new->body[i] = createList();
    }
    return new;
}

/*
Pre-conditions  : toDestroy is properly created.
Post-conditions : hash table is completely destroyed, all memory
                  is freed.
*/
void ht_destroy(Table * toDestroy){
    unsigned size;          /*size of table*/
    int i;                  /*controls loop*/

    size = getSize(toDestroy);
    for (i = 0; i < size; i++){
        destroyList(toDestroy->body[i], destroy_listing);
    }
    free(toDestroy->body);
    destroyList(toDestroy->fullList, empty_destroy_listing);
    free(toDestroy);
}

/*
Pre-conditions  : table is properly initialized.
Post-conditions : returns the size of the table.
*/
unsigned getSize(Table * table){
    if (table != NULL){
        return table->size;
    } else {
        return 0;
    }
}

/*
Pre-conditions  : table is correctly created, key is initialized, 
                  value is initialized.
Post-conditions : value is added to the hash table (both the 
                  body and the full list).  Returns 0 if the 
                  phone number is added, and 1 if it is already 
                  used in the phone book.
*/
int ht_insert(Table * table, char * key, Listing * value){
    unsigned hashVal;           /*returned value from hash function*/
    list * correctList;         /*correct list to insert listing*/
    node * tableNode;           /*node to be inserted into table*/
    node * listNode;            /*node to be inserted into full list*/
    int error = 0;              /*Whether the phone number is already in the system*/

    hashVal = hash(getSize(table), key);
    correctList = table->body[hashVal];
    tableNode = init_node(value);
    listNode = init_node(value);

    error = add_to_sorted_list(correctList, tableNode, 0, listLength(correctList), listing_compare);
    
    if (error){
        destroyNode(listNode, empty_destroy_listing);
        destroyNode(tableNode, destroy_listing);
    } else {
        add_to_sorted_list(table->fullList, listNode, 0, listLength(table->fullList), name_compare);
    }
    return error;
}

/*
Pre-conditions  : table is correctly created, key is initialized
Post-conditions : returns the listing that matches the key.
*/
Listing * ht_lookup(Table * table, char * key){
    node * result;              /*result of search*/
    unsigned hashVal;           /*returned value of hash function*/
    list * correctList;         /*correct list to look in*/

    hashVal = hash(getSize(table), key);

    correctList = table->body[hashVal];

    result = look_through_sorted_list(correctList, key, 0, listLength(correctList), key_compare);
    return getValue(result);
}
    
/*
Pre-conditions  : tableSize and key are initialized.
Post-conditions : returns a hashed value dependent on the key 
                  and table size.
*/
unsigned hash(unsigned tableSize, char * key){
    int len = strlen(key);      /*number of characters to cycle through*/
    int i;                      /*controls loop*/
    int a = 61;                 /*hash value*/
    for (i = 0; i < len; i++){
        a = 29 * a + key[i]; 
    }
    return a % tableSize;
}