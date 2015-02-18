#include "tree.h"
#include "files.h"
#include "fileTree.h"

#include "delete.h"

void delete_main(Tree * tree){
    FileInfo * result;          /*File returned from search*/
    int i;                      /*Used for loops*/

    result = get_file_info("Name of File To Be Deleted: ", tree);

    if (result == NULL){
        printf("Sorry, this entry was not found.\n");
        return;
    }

    if (result->instances > 1){
        printf("There are %d files with this name :\n", result->instances);
        file_info_print_path(result);
        puts("\n");
    }

    for (i = 0; i < result->instances; i++){
        if (!confirm_file(result->path[i])){
            continue;
        }

        if (result->isdir[i] == 1){
            /*Algorithm to check if directory is empty, and then delete it isn't developed yet.*/
            printf("Sorry, currently unable to delete directories.\n");
        } else if (result->instances == 1){
            if (remove(result->path[i]) == 0){
                remove_from_tree(tree, result->name);
                printf("Deletion successful.\n");
                break;
            } else {
                printf("The deletion has failed.\n");
            }                
        } else {
            /*Algorithm to delete a file who shares its name isn't developed.*/
            printf("Sorry, unable to delete the file at this time.\n");
        }

    }
    enter_to_continue();    
}