#include "phoneBook.h"

#define MENU    "\nWelcome To The Phone Book.\n" \
                "Choose One Of The Following Options To Continue :\n" \
                "A - Print Phone Book (By Phone Number)\n" \
                "B - Add New Listing\n" \
                "C - Reverse Lookup (Search By Phone Number)\n" \
                "D - Add Another File To Phone Book\n" \
                "Q - Quit\n"

int main(int argc, char * argv[]){
    Table * table;      /*hash table*/
    char input;         /*input into menu*/

    if (argc != 2){
        printf("Incorrect Usage : should have one(1) command line argument for input file.\n");
        return 1;
    }

    table = make_table_from_file(argv[1]);
    if (table == NULL){
        printf("Invalid input file, please try again with a valid file.\n");
        return 1;
    }

    do {
        printf(MENU);
        input = getchar();
        getchar();
        if (input == 'A' || input == 'a'){
            printList(table->fullList, format_listing_node);
        } else if (input == 'B' || input == 'b'){
            add_new(table);
        } else if (input == 'C' || input == 'c'){
            reverse_lookup(table);
        } else if (input == 'D' || input == 'd'){
            add_file(table);
        }

    } while (input != 'Q' && input != 'q');

    ht_destroy(table);
    return 0;
}
