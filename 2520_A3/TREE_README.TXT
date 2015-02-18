DOCUMENTATION FOR THE AVL BINARY SEARCH TREE ADT

Data Functions - Requirements and Guidelines

For convenience, dataType is the type that will be stored in the BST.

int compare_data(void *, void *)

Both arguments should be pointing to dataType variables.
This should follow the same rules as strcmp; return a 
negative number for less than, a positive number for 
greater than and zero for equal keys.

int sec_compare_data(void *, void *)

This function is optional; the first compare_data function 
can be used for this.  
Alternatively, this function can be used to interface with
the binary tree more easily for search and remove functions
if dataType is complicated.  It is important to note that 
the two functions yield identical results.

Rather than providing a full dataType pointer for the first
argument, this can be of a type that matches the key.  If 
this is done, only the key needs to be provided for the 
search_tree, search_tree_closest and remove_from_tree
functions.

An example of how the two compare functions should differ is
below.

void destroy_data(void *)

This function should completely free all the memory in a given
dataType pointer.

void print_data(void *)

This function should print out what you want printed from the
print_tree function.  Note that the pointer may also be NULL,
in which case you should print something appropriate ie "----".
For the formatting to look the way it should, there should be no
new lines printed.

void collision_resolution(void *, void *)

This function should provide an operation when there is a collision
while adding to the binary search tree.  It will provide two dataType
pointers whose values as per the first compare function are equal.

The first pointer is kept (but can be changed) and the second one 
should be properly freed in this function.

The simplest collision resolution function is this :
void col_res(void * a, void * b){
    destroy_data(b);
}

Alternatively, you may decide to keep an array, linked list or BST
of values with the same key.  The inclusion of this function gives
the user that option.