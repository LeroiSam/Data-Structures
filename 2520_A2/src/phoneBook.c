#include "phoneBook.h"

/*
Pre-conditions  : fileName goes to a valid file with correct format.
Post-conditions : table is created and returned with all the listings 
                  from the file.
*/
Table * make_table_from_file(char fileName[]){
    FILE * inputFH;     /*File handle for input file*/
    Table * table;      /*hash table created and then returned*/
    int lines;          /*number of lines in input file*/

    inputFH = fopen(fileName, "r");
    
    if (inputFH == NULL){
        return NULL;
    }

    lines = number_of_lines(inputFH);
    table = ht_create(lines/2);
    file_to_table(table, inputFH);

    fclose(inputFH);

    return table;
}

/*
Pre-conditions  : toCount is an open file.
Post-conditions : Returns the number of lines in the file.  
                  File is rewinded to the beginning of the file.
*/
int number_of_lines(FILE * toCount){
    int lines = 0;      /*number of lines in file*/
    char line[100];     /*current line from file*/

    while (fgets(line, 99, toCount) != NULL){
        lines++;
    }

    rewind(toCount);

    return lines;
}

/*
Pre-conditions  : table is properly initialized, and toLoad is
                  open (to the beginning of the file).
Post-conditions : All the listings in the file are added to the table.
*/
void file_to_table(Table * table, FILE * toLoad){
    char line[100];     /*line being read to be inputted into hash table*/
    char * first;       /*first name (read from file)*/
    char * last;        /*last name (read from file)*/
    char * phone;       /*phone number (read from file)*/
    Listing * new;      /*listing created (from each line*/

    while (fgets(line, 99, toLoad) != NULL){
        first = strtok(line, ",");
        last = strtok(NULL, ",");
        phone = strtok(NULL, ",");
        new = init_listing(first, last, phone);

        if (ht_insert(table, new->phone, new)){
            fprintf(stderr, "ERROR : %s is already in phone book, listing not added.\n", phone);
        }

    }

    rewind(toLoad);
}

/*
Pre-conditions  : table is properly initialilized
Post-conditions : inputted listing is added to the table.
*/
void add_new(Table * table){
    char temp[100];     /*temporary string (inputted by user)*/
    char first[21];     /*first name (inputted by user)*/
    char last[21];      /*last name (inputted by user)*/
    char phone[11];     /*phone number (inputted by user)*/
    Listing * new;      /*listing created from user input*/

    printf("First Name (Max 20 characters) : ");
    fgets(temp, 99, stdin);
    temp[strlen(temp) - 1] = '\0';
    strcpy(first, temp);
    
    printf("Last Name (Max 20 characters) : ");
    fgets(temp, 99, stdin);
    temp[strlen(temp) - 1] = '\0';
    strcpy(last, temp);
    
    printf("Phone Number (Max 10 characters) : ");
    fgets(temp, 99, stdin);
    temp[strlen(temp) - 1] = '\0';
    strcpy(phone, temp);

    new = init_listing(first, last, phone);
    if (ht_insert(table, new->phone, new) == 1){
        fprintf(stderr, "ERROR : %s is already in the phone book, listing not added\n", phone);
    }
}

/*
Pre-conditions  : table is properly initialized
Post-conditions : listing with inputted phone number is printed. 
*/
void reverse_lookup(Table * table){
    char temp[100];     /*temporary string (inputted by user)*/
    char phone[11];     /*phone number being looked up (inputted by user)*/
    Listing * result;   /*result of search*/

    printf("Phone Number (Max 10 characters) : ");
    fgets(temp, 99, stdin);
    temp[strlen(temp) - 1] = '\0';
    strcpy(phone, temp);

    result = ht_lookup(table, phone);

    if (strcmp(result->phone, phone) != 0){
        printf("No Results Found.\n");
    } else {
        print_listing(result);
    }
}

/*
Pre-conditions  : string has allocated memory, toFormat is properly initialized.
Post-conditions : string holds the information for the listing in the node.
*/
void format_listing_node(char * string, int index, node * toFormat){
    Listing * new;      /*Listing in node being formatted*/

    new = getValue(toFormat);
    sprintf(string, "%s\t%s,%s\n", new->phone, new->last, new->first);
}

void format_listing_node_indexed(char * string, int index, node * toFormat){
    Listing * new;

    new = getValue(toFormat);
    sprintf(string, "%d\t%s\t%s,%s\n", index+1, new->phone, new->last, new->first);
}

void add_file(Table * table){
    char fileName[20];
    char temp[100];
    FILE * newFile;

    printf("File Name : ");
    fgets(temp, 99, stdin);
    temp[strlen(temp) - 1] = '\0';
    strcpy(fileName, temp);

    newFile = fopen(fileName, "r");

    if (newFile == NULL){
        printf("Not a valid file.\n");
    } else {
        file_to_table(table, newFile);
        fclose(newFile);
    }
}
