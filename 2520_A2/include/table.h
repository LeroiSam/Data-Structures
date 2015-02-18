#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listPlus.h"

typedef struct Table{
    unsigned size;
    list * fullList;
    list ** body;    
} Table;

Table * ht_create(unsigned);
void ht_destroy(Table *);
unsigned getSize(Table *);
int ht_insert(Table *, char *, Listing *);
Listing * ht_lookup(Table *, char *);
unsigned hash(unsigned, char *); 