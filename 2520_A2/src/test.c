#include "phoneBook.h"

Table * get_big_table();
void test_search(Table *);
void test_add(Table *);


int main(){
    Table * bigTable;

    bigTable = get_big_table();
    test_search(bigTable);
    test_add(bigTable);

    ht_destroy(bigTable);
    


    return 0;
}

Table * get_big_table(){
    Table * table;
    FILE * inputFH;
    
    printf("IGNORE ALL ERROR MESSAGES HERE, DUPLICATE NUMBERS ARE EXPECTED.\n");

    table = make_table_from_file("input.csv");
    
    inputFH = fopen("input2.csv", "r");
    if (inputFH != NULL){
        file_to_table(table, inputFH);
        fclose(inputFH);
    }
    
    inputFH = fopen("big.csv", "r");
    if (inputFH != NULL){
        file_to_table(table, inputFH);
        fclose(inputFH);
    }

    inputFH = fopen("small.csv", "r");
    if (inputFH != NULL){
        file_to_table(table, inputFH);
        fclose(inputFH);
    }
    printf("\n\nPRINTING THE LIST WITH ALL FOUR INPUT FILES.\n\n");
    printList(table->fullList, format_listing_node_indexed);
    return table;
}

void test_search(Table * table){

    printf("\n\nNOW TESTING WHETHER THE SEARCHING WORKS.\n\n");


    printf("Making searches from each original file... \n");
    printf("3895201910:\tExpected result: Roy Felicia\n");   /*big.csv*/
    print_listing(ht_lookup(table, "3895201910"));
    printf("3895208203:\tExpected result: Lee Beesley\n");
    print_listing(ht_lookup(table, "3895208203"));
    printf("3895243295:\tExpected result: Katherine Meza\n");    /*input.csv*/
    print_listing(ht_lookup(table, "3895243295"));
    printf("3895284792:\tExpected result: Lillian Choi\n");
    print_listing(ht_lookup(table, "3895284792"));
    printf("3895233484:\tExpected result: Winifred Powers\n");      /*input2.csv*/
    print_listing(ht_lookup(table, "3895233484"));
    printf("3895234589:\tExpected result: Claudette Butler\n");       /*small.csv*/
    print_listing(ht_lookup(table, "3895234589"));
}

void test_add(Table * table){
    Listing * new;
    char first[21];
    char last[21];
    char phone[11];
    int hashV;

    printf("\n\nNOW TESTING ADDING A NEW LISTING.\n\n");

    strcpy(first, "John");
    strcpy(last, "Smith");
    strcpy(phone, "3895269999");

    new = init_listing(first, last, phone);
    printf("Created A New Listing:\n");
    print_listing(new);
    hashV = hash(getSize(table), new->phone);
    printf("Hash Value is : %d\n", hashV);
    printf("Length of this list before insertion is : %d\n", listLength(table->body[hashV]));
    ht_insert(table, new->phone, new);
    printf("Length of this list after insertion is : %d\n", listLength(table->body[hashV]));
    printf("Now, to check that this inner list is sorted (by phone number), it will be printed.\n");
    printList(table->body[hashV], format_listing_node);
}

