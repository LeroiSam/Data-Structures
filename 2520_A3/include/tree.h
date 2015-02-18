#include <stdlib.h>
#include <stdio.h>

#define MAX(A, B)   {(A) > (B) ? (A) : (B)}

typedef struct TreeInformation{
    int (*compare_data)(void *, void *);
    int (*sec_compare_data)(void *, void *);
    void (*destroy_data)(void *);
    void (*print_data)(void *);
    void (*collision_resolution)(void *, void *);
} TreeInfo;

typedef struct AVLTree{
    struct AVLTree * left;
    struct AVLTree * right;
    void * data;
    TreeInfo * info;
    int height;
} Tree;
Tree * init_tree(int (*compare)(void *, void *), 
                 int (*sec_compare)(void *, void *), 
                 void (*destroy)(void *), 
                 void (*print)(void *), 
                 void (*collide)(void *, void *));

void destroy_tree(Tree *);

void * search_tree(Tree *, void *);

void * search_tree_closest(Tree *, void *);

Tree * add_to_tree(Tree *, void *);

void remove_from_tree(Tree *, void *);

void print_tree(Tree *);

int get_height(Tree *);

Tree * safe_left(Tree *);

Tree * safe_right(Tree *);

void * safe_data(Tree * a);