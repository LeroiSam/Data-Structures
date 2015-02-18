#include "colors.h"
#include "files.h"
#include "menus.h"
#include "tree.h"
#include "fileTree.h"

#include "search.h"


int search(Tree * tree){
    char input;             /*input for the menu*/
    int quitting = 0;       /*whether or not the user is quitting the program*/
    int returning = 0;      /*whether or not the user is returning to the main menu*/

    do {
        color_puts(SEARCHMENU, COLOR_CYAN);
        putchar('>');
        input = getchar();
        while (getchar() != '\n');
        if (input == 'a' || input == 'A'){
            /*Basic Search*/
            basic_search(tree);
        } else if (input == 'b' || input == 'B'){
            /*Search By First Letter*/
            first_letter_search(tree);
        } else if (input == 'c' || input == 'C'){
            /*Search By Range*/
            range_search(tree);
        } else if (input == 'd' || input == 'D'){
            /*Regex Search*/
            regex_search(tree);
        } else if (input == 'm' || input == 'M'){
            returning = 1;
        } else if (input == 'q' || input == 'Q'){
            quitting = 1;
        } else {
            printf("Invalid Input.  Please choose A, B, C, D, M, or Q\n");
        }
        if (toupper(input) <= 'D'){
            enter_to_continue();
        }
    } while (!quitting && !returning);
    return quitting;
}

/*
Description     : Basic search for a file with an inputted name.
*/
void basic_search(Tree * tree){
    FileInfo * result;              /*result of search*/

    result = get_file_info("Name Of File: ", tree);

    if (result == NULL){
        printf("Sorry, this entry was not found.\n");
    } else {
        file_info_print_path(result);
        putchar('\n');
    }

}
/*
Description     : Searches the tree for entries starting with inputted letter.
Note            : Uses the same process as range_search (ie first_letter_search 
                  for c is the same as range search from c to d).
*/
void first_letter_search(Tree * tree){
    char input;             /*first letter of user input*/
    char firstString[2];    /*input as a string*/
    char secondString[2];   /*next letter as a string*/
    FileInfo ** results;    /*array of FileInfo pointers, results of search*/
    int matches;            /*number of matches to search*/
    int i;                  /*controls the loop*/

    printf("Letter To Search: ");
    input = getchar();
    while (getchar() != '\n');
    printf("Searching For Entries starting with %c.\n\n", input);

    firstString[0] = input;
    firstString[1] = '\0';
    secondString[0] = input + 1;
    secondString[1] = '\0';
    results = alpha_search(tree, firstString, secondString, &matches);

    for (i = 0; i < matches; i++){
        file_info_print_path(results[i]);
        putchar('\n');
    }
    if (matches == 0){
        printf("No files matched your search.\n");
    }
    free(results);
}

/*
Description     : Searches the tree and returns all of the entries in a given range.
Notes           : Includes the lower bound, excludes the upper bound.
*/
void range_search(Tree * tree){
    char first[256];            /*lower bound string*/
    char last[256];             /*upper bound string*/
    FileInfo ** results;        /*array of FileInfo pointers, results of search*/
    int matches = 0;            /*number of matches to search*/
    int i;                      /*controls the loop*/

    printf("Lower Bound : ");
    fgets(first, 255, stdin);
    first[strlen(first) - 1] = '\0';

    printf("Upper Bound : ");
    fgets(last, 255, stdin);
    last[strlen(last) - 1] = '\0';
    if (strlen(last) == 0){
        last[0] = 127;
        last[1] = '\0';
    }

    results = alpha_search(tree, first, last, &matches);
    putchar('\n');

    for (i = 0; i < matches; i++){
        file_info_print_path(results[i]);
        putchar('\n');
    }
    if (matches == 0){
        printf("No files matched your search.\n");
    }

    free(results);
}

/*
Description     : Performs a search using regular expressions.
Note            : Only manageable way to do this is to check 
                  against every entry in the tree.  
*/
void regex_search(Tree * tree){
    FileInfo ** alphaResults = NULL;        /*a list of all the files in the tree*/
    char input[256];                        /*user input for regex*/
    char first[2];                          /*contains lower bound string*/
    char second[2];                         /*contains upper bound string*/
    regex_t regex;                          /*input as a regular expression*/
    int invalidRegex;                       /*whether or not the regex was invalid*/
    int alphaMatches = 0;                   /*number of matches to alpha search*/
    int matches = 0;                        /*number of matches to regex search*/
    int i;                                  /*controls loops*/

    printf("Regex : ");
    fgets(input, 255, stdin);
    input[strlen(input) - 1] = '\0';
    invalidRegex = regcomp(&regex, input, 0);

    if (invalidRegex){
        printf("The syntax for your regular expression was not valid.\n");
    } else {
        first[0] = 0;
        first[1] = '\0';
        second[0] = 127;
        second[1] = '\0';
        alphaResults = alpha_search(tree, first, second, &alphaMatches);
        putchar('\n');
        for (i = 0; i < alphaMatches; i++){
            if (regexec(&regex, alphaResults[i]->name, 0, NULL, 0) == 0){
                file_info_print_path(alphaResults[i]);
                putchar('\n');
                matches++;
            }
        }

        if (matches == 0){
            printf("No files matched your search.\n");
        }
    }
    free(alphaResults);
    regfree(&regex);
}
/*
Description     : Finds all the matches in a range.
Pre-conditions  : tree is loaded, lower and upper are initialized.
Post-conditions : returns an array of all the entries in the given range.
*/
FileInfo ** alpha_search(Tree * tree, char * lower, char * upper, int * matches){
    FileInfo ** results = NULL; 
    FileInfo ** temp;
    FileInfo * currentMatch;
    int passedBounds = 0;
    int (*comp)(void *, void *) = &file_info_sec_compare;
    *matches = 0;
    do {
        currentMatch = search_tree_closest(tree, lower);
        if (currentMatch == NULL){
            passedBounds = 1;
        } else if (comp(upper, currentMatch) > 0){
            *matches += 1;
            temp = realloc(results, sizeof(FileInfo *) * (*matches));
            if (temp == NULL){
                free(results);
                exit(1);
            }
            results = temp;
            results[*matches - 1] = currentMatch;
            sprintf(lower, "%s%c", currentMatch->name, 21);
        } else {
            passedBounds = 1;
        }
    } while (!passedBounds);
    return results;
}