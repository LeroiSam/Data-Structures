#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Listing{
    char last[21];
    char first[21];
    char phone[11];
} Listing;

Listing * init_listing(char *, char *, char *);
void destroy_listing(Listing *);
void empty_destroy_listing(Listing *);
void print_listing(Listing *);
