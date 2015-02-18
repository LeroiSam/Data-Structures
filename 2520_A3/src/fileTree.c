#include "tree.h"
#include "files.h"

#include "fileTree.h"

FileInfo * get_file_info(const char * action, Tree * tree){
    FileInfo * result;      /*result of search, returned value*/
    char input[256];        /*hold user input*/

    printf("%s", action);
    fgets(input, 255, stdin);
    input[strlen(input) - 1] = '\0';
    result = search_tree(tree, input);

    return result;
}

int confirm_file(char * toConfirm){
    char confirm;       /*Whether or not the user has confirmed*/

    printf("Is this the file/directory you were looking for? (y/n)\n");
    printf("%s\n", toConfirm);
    confirm = getchar();
    while (getchar() != '\n');
    return (toupper(confirm) == 'Y');
}

void enter_to_continue(){
    printf("PRESS ENTER TO CONTINUE.");
    while (getchar() != '\n');
    putchar('\n');
}

void get_parent_path_name(char * path){
    int j = 0;          /*Position of null terminator*/
    int k = 0;          /*Controls loop*/
    
    do {
        j = (path[k] == '/') ? k : j;
        k++;
    } while (path[k-1] != '\0');
    
    path[j+1] = '\0';

}