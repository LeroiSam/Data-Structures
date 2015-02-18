#include "files.h"
#include "tree.h"
#include "fileTree.h"

#include "move.h"
/*
Description     : Moves files from one directory to another.
Notes           : Input should be the directory's name (path not included).
*/
void move_main(Tree * tree){
    FileInfo * result;      /*result of search*/
    int i;                  /*controls loop*/
    int instances;          /*number of files with this name*/

    result = get_file_info("Name of file to be moved: ", tree);

    if (result == NULL){
        printf("Sorry, this entry was not found.\n");
        enter_to_continue();
        return;
    }

    instances = result->instances;

    if (instances > 1){
        printf("There are %d files with this name :\n", instances);
        file_info_print_path(result);
        puts("\n");
    }

    for (i = 0; i < instances; i++){
        if (!confirm_file(result->path[i])){
            continue;
        }

        if (result->isdir[i]){
            /*This is a directory*/
            printf("Sorry, directories cannot be moved.\n");
        } else {
            /*This is a file*/
            if (move_file(result, tree, i)){
                break;
            }
        }
    }

    enter_to_continue();
}

int move_file(FileInfo * toMove, Tree * tree, int current){
    FileInfo * newDirInfo;      /*FileInfo of the file's new directory*/
    int j;                      /*Controls the loop*/

    newDirInfo = get_file_info("Name of new directory: ", tree);

    if (dir_count(newDirInfo) == 0){
        printf("Sorry, there is no directory with this name.\n");
        return 0;
    } else if (dir_count(newDirInfo) > 1){
        printf("There are %d directories in this system with this name.\n", dir_count(newDirInfo));
    }

    for (j = 0; j < newDirInfo->instances; j++){
        if (newDirInfo->isdir[j]){
            if (confirm_file(newDirInfo->path[j])){
                char newPath[256];
                sprintf(newPath, "%s/%s", newDirInfo->path[j], toMove->name);
                if (rename(toMove->path[current], newPath) == 0){
                    free(toMove->path[current]);
                    toMove->path[current] = malloc(sizeof(char) * (strlen(newPath) + 1));
                    strcpy(toMove->path[current], newPath);
                    printf("Move successful.\n");
                } else {
                    printf("The move has failed.\n");
                }
                return 1;
            }
        }
    }
    return 0;
}

int dir_count(FileInfo * entry){
    int i;                  /*Controls loop*/
    int count = 0;          /*Number of directories held in entry*/

    if (entry == NULL){return 0;}
    for (i = 0; i < entry->instances; i++){
        if (entry->isdir[i]){
            count++;
        }
    }
    return count;
}