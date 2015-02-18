#include "listing.h"

/*
Pre-conditions  : first, last and phone are initialized to 
                  strings with at least 21, 21, and 11 
                  characters allocated respectively.
Post-conditions : returns new listing with the inputted data.
*/
Listing * init_listing(char * first, char * last, char * phoneNumber){
    Listing * new;      /*listing being created*/

    new = malloc(sizeof(Listing));

    strncpy(new->last, last, 20);
    new->last[20] = '\0';

    strncpy(new->first, first, 20);
    new->first[20] = '\0';

    strncpy(new->phone, phoneNumber, 10);
    new->phone[10] = '\0';
    
    return new;
}


/*
Description     : destroy function that frees listing.
*/
void destroy_listing(Listing * toDestroy){
    free(toDestroy);
}

/*
Description     : empty destroy function that does nothing.
                  Used instead of destroy to destroy list or 
                  node without listing.
*/
void empty_destroy_listing(Listing * toDestroy){
}

/*
Pre-conditions  : toPrint is properly initialized.
Post-conditions : Listing is printed in format : PHONENUMBER    FIRST LAST
*/
void print_listing(Listing * toPrint){
    printf("%s\t%s,%s\n", toPrint->phone, toPrint->last, toPrint->first);
}
