#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FileInfo * get_file_info(const char * action, Tree * tree);
int confirm_file(char * toConfirm);
void enter_to_continue();
void get_parent_path_name(char *);
