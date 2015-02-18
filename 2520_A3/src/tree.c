#include "tree.h"

void rec_destroy_tree(Tree *);
void delete_node(Tree *);

Tree * insert(Tree *, Tree *);
Tree * right_rotation(Tree *);
Tree * left_rotation(Tree *);
Tree * left_right_rotation(Tree *);
Tree * right_left_rotation(Tree *);

void rec_print_tree(Tree *, int, int, void (*print)(void *));
int remove_tree(Tree *, void *);
Tree * get_successor(Tree * a);

int max(int, int);
int balance_factor(Tree *);

/*
Description     : Initializes the binary tree with all the functions necessary to use it.
Pre-conditions  : For specifications regarding each function, see the README.txt.
Post-conditions : Returns an empty tree with the functions loaded into it.
*/

Tree * init_tree(int (*compare)(void *, void *), 
                 int (*sec_compare)(void *, void *), 
                 void (*destroy)(void *), 
                 void (*print)(void *), 
                 void (*collide)(void *, void *)){

    Tree * new = malloc(sizeof(Tree));
    new->left = NULL;
    new->right = NULL;
    new->data = NULL;
    new->height = -1;
    new->info = malloc(sizeof(TreeInfo));
    new->info->compare_data = compare;
    new->info->sec_compare_data = sec_compare;
    new->info->destroy_data = destroy;
    new->info->print_data = print;
    new->info->collision_resolution = collide;
    return new;
}

/*
Description     : Destroys the binary tree and uses the destroy function provided in init_tree to destroy all the data.
Pre-conditions  : Tree must be initialized with init_tree.
Post-conditions : Tree is completely freed as per the destroy function provided.
*/
void destroy_tree(Tree * toDestroy){
    TreeInfo * temp = toDestroy->info;
    rec_destroy_tree(toDestroy);
    free(temp);
}
/*Used internally only by destroy_tree*/
void rec_destroy_tree(Tree * toDestroy){
    if (toDestroy != NULL){
        rec_destroy_tree(toDestroy->left);
        rec_destroy_tree(toDestroy->right);
        delete_node(toDestroy);
    }
}
/*Used internally only by destroy_tree and remove_from_tree*/
void delete_node(Tree * toDelete){
    toDelete->info->destroy_data(toDelete->data);
    free(toDelete);
}

/*
Description     : Searches the tree
Pre-conditions  : Takes the tree as the first argument.  
                  Second argument should match the type 
                  of the second compare function's first argument.
Post-conditions : Returns NULL if data not found, the data upon
                  success (same type as second compare function's 
                  second argument).
*/
void * search_tree(Tree * toSearch, void * findThis){
    int result;

    if (toSearch == NULL){
        return NULL;
    }
    result = toSearch->info->sec_compare_data(findThis, toSearch->data);
    if (result < 0){
        return search_tree(toSearch->left, findThis);
    } else if (result > 0){
        return search_tree(toSearch->right, findThis);
    } else {
        return toSearch->data;
    }
}

/*
Description     : Identical to search_tree but will find next closest
                  data ("rounding up")
Pre-conditions  : Takes the tree as the first argument.  
                  Second argument should match the type 
                  of the second compare function's first argument.
Post-conditions : Returns data from next closest tree member if data 
                  not found, the data upon success (same type as 
                  second compare function's second argument).
*/
void * search_tree_closest(Tree * toSearch, void * findThis){
    int result;
    void * temp;
    if (toSearch == NULL){
        return NULL;
    }
    result = toSearch->info->sec_compare_data(findThis, toSearch->data);
    if (result < 0){
        temp = search_tree_closest(toSearch->left, findThis);
        if (temp == NULL){
            return toSearch->data;
        } else {
            return temp;
        }
    } else if (result > 0){
        return search_tree_closest(toSearch->right, findThis);
    } else {
        return toSearch->data;
    }
}
/*
Description     : Adds a new member to the binary tree. 
Pre-conditions  : tree - binary tree to add to.
                  data - new member to add to the tree.
Post-conditions : Returns the tree.  This shouldn't be 
                  ignored because address will change if
                  tree's head changes.
*/
Tree * add_to_tree(Tree * tree, void * data){
    if (get_height(tree) > -1){
        Tree * new = malloc(sizeof(Tree));
        new->data = data;
        new->info = tree->info;
        return insert(tree, new);
    } else {
        tree->data = data;
        tree->height = 0;
        return tree;
    }
}
/*Used internally only by add_to_tree*/
Tree * insert(Tree * tree, Tree * new){
    int result;
    if (tree == NULL){
        tree = new;
        tree->height = 0;
        tree->left = NULL;
        tree->right = NULL;
        return tree;
    }
    result = tree->info->compare_data(new->data, tree->data);
    if (result < 0){
        tree->left = insert(tree->left, new);
        if (balance_factor(tree) == 2){
            int resultB = tree->info->compare_data(new->data, tree->left->data);
            if (resultB < 0){
                tree = right_rotation(tree);
            } else {
                tree = left_right_rotation(tree);
            }
        }
    } else if (result > 0) {
        tree->right = insert(tree->right, new);
        if (balance_factor(tree) == -2){
            int resultB = tree->info->compare_data(new->data, tree->right->data);
            if (resultB < 0){
                tree = right_left_rotation(tree);
            } else {
                tree = left_rotation(tree);
            }
        }
    } else {
        tree->info->collision_resolution(tree->data, new->data);
        free(new);
    }

    tree->height = max(get_height(tree->left), get_height(tree->right)) + 1;
    return tree;
}
/*Used internally only by add_to_tree*/
Tree * right_rotation(Tree * a){
    Tree * b = a->left;
    a->left = b->right;
    b->right = a;

    a->height = max(get_height(a->left), get_height(a->right)) + 1;
    b->height = max(get_height(b->left), get_height(b->right)) + 1;

    return b;
}
/*Used internally only by add_to_tree*/
Tree * left_rotation(Tree * a){
    Tree * b = a->right;
    a->right = b->left;
    b->left = a;

    a->height = max(get_height(a->left), get_height(a->right)) + 1;
    b->height = max(get_height(b->left), get_height(b->right)) + 1;

    return b;
}
/*Used internally only by add_to_tree*/
Tree * left_right_rotation(Tree * a){
    a->left = left_rotation(a->left);
    return right_rotation(a);
}
/*Used internally only by add_to_tree*/
Tree * right_left_rotation(Tree * a){
    a->right = right_rotation(a->right);
    return left_rotation(a);
}

/*
Description     : Removes a data item from the tree.
Pre-conditions  : tree - root node of tree to remove data item from.
                  data - data to remove (should match first argument
                  of second compare function).
Post-conditions : tree has data removed if it is found.
                  data is destroyed as per destroy function provided
*/
void remove_from_tree(Tree * tree, void * data){
    remove_tree(tree, data);
}

/*Used internally by remove_from_tree*/
/*Used so that return data is not available to user*/
int remove_tree(Tree * tree, void * toRemove){
    int compare = tree->info->sec_compare_data(toRemove, safe_data(tree));
    if (compare < 0){
        if (remove_tree(safe_left(tree), toRemove)){
            tree->left = NULL;
        }
    } else if (compare > 0){
        if (remove_tree(safe_right(tree), toRemove)){
            tree->right = NULL;
        }
    } else {
        Tree * successor = get_successor(tree);
        if (successor == NULL){
            successor = safe_left(tree);
            if (successor == NULL){
                delete_node(tree);
                return 1;
            } else {
                void * temp = tree->data;
                tree->data = successor->data;
                successor->data = temp;
                if (remove_tree(tree->left, toRemove)){
                    tree->left = NULL;
                }
            }
        } else {
            /*swap with successor*/
            void * temp = tree->data;
            tree->data = successor->data;
            successor->data = temp;
            if (remove_tree(tree->right, toRemove)){
                tree->right = NULL;
            }
        }
    }
    tree->height = max(get_height(tree->left), get_height(tree->right)) + 1;
    return 0;
}

/*Used internally by remove_from_tree*/
Tree * get_successor(Tree * a){
    Tree * b = safe_right(a);
    while (safe_left(b) != NULL){
        b = safe_left(b);
    }
    return b;
}
/*
Description     : Prints tree in visual format using the print 
                  function provided.
Pre-conditions  : Tree is initialized with tree_init.
Post-conditions : Tree is printed visually, no change is made to
                  variables.
*/
void print_tree(Tree * toPrint){
    rec_print_tree(toPrint, 0, get_height(toPrint), toPrint->info->print_data);
}

/*Internal Use Only By print_tree; recursive body of function*/
void rec_print_tree(Tree * toPrint, int current, int levels, void (*print_entry)(void *)){
    int i;
    if (current < levels){
        rec_print_tree(safe_left(toPrint), current + 1, levels, print_entry);
    }

    for (i = 0; i < current; i++) {putchar('\t');}
    print_entry(safe_data(toPrint));
    /*printf(":%d", balance_factor(toPrint));*/
    putchar('\n');

    if (current < levels){
        rec_print_tree(safe_right(toPrint), current + 1, levels, print_entry);
    }
}

/*
Description     : Gets the height of a tree.
Pre-conditions  : None.
Post-conditions : Returns height of tree (-1 if NULL).
*/
int get_height(Tree * tree){
    return (tree == NULL) ? -1 : tree->height;
}

/*
Description     : Gets the left subtree of the tree.
Pre-conditions  : None.
Post-conditions : Returns the left subtree of the tree (NULL if NULL).
*/
Tree * safe_left(Tree * a){
    return (a != NULL) ? a->left : NULL;
}

/*
Description     : Gets the right subtree of the tree.
Pre-conditions  : None.
Post-conditions : Returns the right subtree of the tree (NULL if NULL).
*/
Tree * safe_right(Tree * a){
    return (a != NULL) ? a->right : NULL;
}

/*
Description     : Gets the root data of the tree.
Pre-conditions  : None.
Post-conditions : Returns the root data of the tree (NULL if NULL).
*/
void * safe_data(Tree * a){
    return (a != NULL) ? a->data : NULL;
}

/*Internal Use Only, finds max of two integers.*/
int max(int a, int b){
    return (a > b ? a : b);
}

/*Internal Use Only, finds balance factor of a tree.*/
int balance_factor(Tree * a){
    return get_height(safe_left(a)) - get_height(safe_right(a));
}