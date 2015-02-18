#include "files.h"
#include "tree.h"
#include "fileTree.h"

#include "rename.h"

/*
Description     : Renames a file with a name given by the user.
Notes           : Does not work for directories or files with 
                  names that are shared.
*/

void rename_main(Tree ** tree){
    char input[256];                            /*Name of file to be moved*/
    FileInfo * result;                          /*file with old name*/
    FileInfo * replacement;                     /*file with new name*/
    char * path = malloc(sizeof(char) * 256);   /*path of file's parent directory*/
    int i;                                      /*controls loop*/

    result = get_file_info("Name of File To Be Renamed: ", *tree);

    if (result == NULL){
        printf("Sorry, this entry was not found.\n");
        free(path);
        enter_to_continue();
        return;
    }

    if (result->instances > 1){
        printf("There are %d files with this name :\n", result->instances);
        file_info_print_path(result);
        puts("\n");
    }

    for (i = 0; i < result->instances; i++){
        if (confirm_file(result->path[i])){
            if (result->isdir[i]){
                printf("Sorry, directories cannot be renamed at this time.\n");
            } else if (result->instances > 1){
                printf("Sorry, currently unable to rename this file.\n");
            } else {
                printf("Please input the new name for this file : ");
                fgets(input, 255, stdin);
                input[strlen(input) - 1] = '\0';

                /*Makes the full path of the new file.*/
                strcpy(path, result->path[i]);
                get_parent_path_name(path);
                path = strcat(path, input);

                replacement = file_info_init(input, path, 0);
                if (rename(result->path[i], replacement->path[i]) == 0){
                    remove_from_tree(*tree, result->name);
                    *tree = add_to_tree(*tree, replacement);
                    printf("Rename successful.\n");
                    break;
                } else {
                    printf("Renaming has failed.\n");
                }
            }
        }
    }
    free(path);
    enter_to_continue();
}