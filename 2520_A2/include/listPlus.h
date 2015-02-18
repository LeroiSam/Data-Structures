#include <stdlib.h>
#include "list.h"

#define CEIL(a, b) (((a) / (b)) + (((a) % (b)) > 0 ? 1 : 0))

int add_to_sorted_list(list *, node *, unsigned, unsigned, int (*compar)(const void *, const void *));
node * look_through_sorted_list(list *, char *, unsigned, unsigned, int (*compar)(const void *, const void *));

node * getElement(list *, unsigned);

int listing_compare(void const *a, void const *b); 
int key_compare(void const *a, void const *b);
int name_compare(void const *a, void const *b);
