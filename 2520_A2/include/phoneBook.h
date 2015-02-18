#include <stdlib.h>
#include <stdio.h>
#include "table.h"

Table * make_table_from_file(char []);
int number_of_lines(FILE *);
void file_to_table(Table *, FILE *);
void format_listing_node(char *, int, node *);
void format_listing_node_indexed(char *, int, node *);
void add_new(Table *);
void reverse_lookup(Table *);
void add_file(Table *);
