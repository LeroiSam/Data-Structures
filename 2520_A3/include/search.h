#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>

int search(Tree *);
void basic_search(Tree *);
void first_letter_search(Tree *);
void range_search(Tree *);
void regex_search(Tree *);
FileInfo ** alpha_search(Tree *, char *, char *, int *);
void delete_main(Tree *);