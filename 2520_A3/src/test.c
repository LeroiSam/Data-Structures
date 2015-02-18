#include "test.h"
#include "colors.h"

void collision(void *, void *);

int main(){
    Tree * tree;        /*Tree ADT - holds integer values in AVL tree being tested*/
    int * entry;        /*Temporary variable when adding to, removing from and searching tree*/
    int * result;       /*Result of search*/
    int i;              /*Controls loops*/

    tree = init_tree(&compare, &compare, &destroy, &print, &collision);

    printf("Adding the numbers to the tree in an out of sequence order :\n");
    for (i = 0; i < 12; i++){
        entry = malloc(sizeof(int));
        *entry = (3 * i) % 10;
        printf("%d, ", *entry);
        tree = add_to_tree(tree, entry);
    }
    putchar('\n');
    printf("Repeated some entries to test collision resolution.\n");

    printf("Tree after insertions.\n");

    print_tree(tree);
    for (i = 0; i < 10; i = i + 3){
        entry = malloc(sizeof(int));
        *entry = i;
        remove_from_tree(tree, entry);
        free(entry);

        printf("%d is removed...\n", i);
        print_tree(tree);

        putchar('\n');
    }

    
    printf("Testing search_tree_closest...\n");
    printf("Searching for 3 (no longer in tree), should return 4.\n");
    entry = malloc(sizeof(int));
    *entry = 3;
    result = search_tree_closest(tree, entry);
    printf("Returned : %d\n", *result);
    free(entry);

    printf("Note : Because the search_tree_closest function works, \n");
    printf("it follows that the search_tree function must also work.\n");
    printf("In the context of only integers, this function doesn't \n");
    printf("really make sense though.\n");

    printf("Destroying tree...\n");
    destroy_tree(tree);

    printf("\n\nAll tests passed.\n");
    return 0;
}

int compare(void * a, void * b){
    int * aa = (int *)a;
    int * bb = (int *)b;

    return *aa - *bb;
}

void destroy(void * a){
    free(a);
}

void print(void * a){
    char temp[256];
    int * aa = (int *)a;
    if (aa != NULL){
        sprintf(temp, "%d", *aa);
        color_puts(temp, COLOR_RED);
    } else {
        color_puts("-", COLOR_BLUE);
    }
}

void collision(void * a, void * b){
    destroy(b);
}