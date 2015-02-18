#include "main.h"

#include "delete.h"
#include "move.h"
#include "rename.h"
#include "search.h"

int main(int argc, char * argv[]){
    Tree * tree = config(argc, argv);
    if (tree == NULL){
        return 1;
    }
    menu(&tree);
    destroy_tree(tree);
    return 0;
}

/*Outputs menu, calls appropriate functions on input*/
void menu(Tree ** tree){
    int quitting = 0;           /*whether or not the user is quitting*/
    char input;                 /*input from user*/
    do {
        color_puts(MAINMENU, COLOR_CYAN);
        putchar('>');
        input = getchar();
        while (getchar() != '\n');
        if (input == 'a' || input == 'A'){
            /*Search For File*/
            quitting = search(*tree);
        } else if (input == 'b' || input == 'B'){
            /*Delete File*/
            delete_main(*tree);
        } else if (input == 'c' || input == 'C'){
            /*Rename File*/
            rename_main(tree);
        } else if (input == 'd' || input == 'D'){
            /*Move File*/
            move_main(*tree);
        } else if (input == 'e' || input == 'E'){
            /*Uncomment line below while debugging to print tree.*/
            /*print_tree(*tree);*/
        } else if (input == 'q' || input == 'Q'){
            quitting = 1;
        } else {
            printf("This Is Not A Valid Option.  Please Choose A, B, C, D, or Q to Quit.\n\n");
        }
    } while (!quitting);
}

Tree * config(int argc, char * argv[]){
    char * path = malloc(sizeof(char) * 256);       /*the relative path to the directory*/
    int temp;                                       /*temporary variable */
    Tree * tree;                                    /*binary tree being initialized*/

    strcpy(path, argc > 1 ? argv[1] : DEFAULT_DIR);

    /*gets rid of trailing slashes*/
    do {
        temp = strlen(path) - 1;
        path[temp] = path[temp] == '/' ? '\0' : path[temp];
    } while (strlen(path) - 1 != temp);
    /*full_list(path);*/

    tree = init_tree(&file_info_compare, &file_info_sec_compare, &file_info_destroy, &file_info_print_name, &file_info_coll_res);
    load_tree(&tree, path);
    free(path);
    return tree;
}

void load_tree(Tree ** tree, char * chosenPath){
    load_tree_recursive(tree, chosenPath, chosenPath, 0);
}

int load_tree_recursive(Tree ** tree, char * currentPath, char * newAddition, int level){
    DIR * directory;            /*Pointer to current directory stream*/
    FileInfo * newInfo;         /*The file information of the file being added*/
    struct dirent * a;          /*member in the directory stream*/
    char * curDir;              /*current directory*/
    int isDir;                  /*if the current file is a directory*/
    
    if (chdir(newAddition) == 0){
        curDir = getcwd(NULL, 0);
        directory = opendir(curDir);
        free(curDir);
        while ((a = readdir(directory))){
            if (strcmp(".", a->d_name) != 0 && strcmp("..", a->d_name) != 0){
                char * b = malloc(sizeof(char) * (strlen(currentPath) + strlen(a->d_name) + 2));
                sprintf(b, "%s/%s", currentPath, a->d_name);
                isDir = load_tree_recursive(tree, b, a->d_name, level + 1);
                newInfo = file_info_init(a->d_name, b, isDir);
                *tree = add_to_tree(*tree, newInfo);
                free(b);
            }
        }
        closedir(directory);
        chdir("..");
        return 1;
    }
    
    return 0;
}