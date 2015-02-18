#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "colors.h"
#include "files.h"
#include "menus.h"
#include "tree.h"

#define DEFAULT_DIR "example"

void load_tree(Tree **, char *);
int load_tree_recursive(Tree **, char *, char *, int);
Tree * config(int, char *[]);
void menu(Tree **);
