#include "files.h"
#include "colors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FileInfo * file_info_init(char * name, char * path, int isdir){
    FileInfo * new;         /*new FileInfo struct being created*/

    new = malloc(sizeof(FileInfo));

    new->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(new->name, name);

    new->path = malloc(sizeof(char *));
    new->path[0] = malloc(sizeof(char) * (strlen(path) + 1));
    strcpy(new->path[0], path);

    new->instances = 1;

    new->isdir = malloc(sizeof(int));
    new->isdir[0] = isdir;

    return new;
}

void file_info_coll_res(void * a, void * b){
    FileInfo * aa = (FileInfo *)a;      /*The entry being kept in the tree*/
    FileInfo * bb = (FileInfo *)b;      /*The entry which collided*/
    int k = aa->instances;              /*The number of paths contained in this entry*/


    aa->path = realloc(aa->path, sizeof(char *) * (k+1));
    aa->isdir = realloc(aa->isdir, sizeof(int) * (k+1));
    if (aa->path == NULL){
        printf("Out Of Usable Memory.\n");
        exit(1);
    }
    aa->path[k] = bb->path[0];
    aa->isdir[k] = bb->isdir[0];
    free(bb->path);
    free(bb->name);
    free(bb->isdir);
    free(bb);
    aa->instances++;
}

int file_info_compare(void * a, void * b){
    FileInfo * aa = (FileInfo *)a;
    FileInfo * bb = (FileInfo *)b;

    return strcmp(aa->name, bb->name);
}

int file_info_sec_compare(void * a, void * b){
    char * aa = (char *)a;              /*key for comparison*/
    FileInfo * bb = (FileInfo *)b;      /*entry for comparison*/

    return strcmp(aa, bb->name);
}

void file_info_print_name(void * a){
    FileInfo * aa = (FileInfo *)a;      /*entry with name to be printed*/
    char temp[256];                     /*temporary variable, holds string to be printed*/

    if (aa != NULL){
        sprintf(temp, "%s", aa->name);
        if (aa->instances > 1){
            color_puts(temp, COLOR_RED);
        } else if (aa->isdir[0] == 1){
            color_puts(temp, COLOR_BLUE);
        } else {
            color_puts(temp, COLOR_GREEN);
        }
    } else {
        color_puts("--------", COLOR_YELLOW);
    }
}

void file_info_print_path(void * a){
    FileInfo * aa = (FileInfo *)a;      /*entry with path(s) to be printed*/
    char temp[256];                     /*temporary variable, holds string to be printed*/
    int i;                              /*controls loop*/

    if (aa != NULL){
        for (i = 0; i < aa->instances; i++){
            sprintf(temp, "%s", aa->path[i]);
            if (aa->isdir[i] == 1){
                color_puts(temp, COLOR_BLUE);
            } else {
                color_puts(temp, COLOR_GREEN);
            }
            if (i+1 < aa->instances){putchar('\n');}
        }
    } else {
        color_puts("--------", COLOR_YELLOW);
    }
}

void file_info_destroy(void * a){
    FileInfo * aa = (FileInfo *)a;      /*entry to destroy*/
    int i;                              /*controls loop*/

    free(aa->name);
    for (i = 0; i < aa->instances; i++){
        free(aa->path[i]);
    }
    free(aa->path);
    free(aa->isdir);
    free(aa);
}

char * get_name(FileInfo * info){
    return info != NULL ? info->name : NULL;
}

char ** get_path(FileInfo * info){
    return info != NULL ? info->path : NULL;
}