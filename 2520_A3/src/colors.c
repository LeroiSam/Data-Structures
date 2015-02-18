#include "colors.h"

int color_puts(const char * str, const char * color){
    int returnVal;      /*Return value from fputs call with string*/

    if (COLOR_ON){
        fputs(color, stdout);
    }
    returnVal = fputs(str, stdout);
    if (COLOR_ON){
        fputs(COLOR_RESET, stdout);
    }
    return returnVal;
}