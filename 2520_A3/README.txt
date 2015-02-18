*******************
NOTES ON USAGE:
*******************

For the command line argument, the program takes the 
relative path of the directory (no the complete path).

ie ./bin/main example
NOT
./bin/main ~/CIS2520/CooperDylanA3/example

When using the main program, the path of a file or 
directory should NOT be typed by the user, just the name.

ie. when prompted for file's name type:
horse
NOT
example/dragon/horse
OR
~/CIS2520/CooperDylanA3/example/dragon/horse

*******************
DESIGN CHOICES
*******************

Choice: Separate menu for search options.
Reason: The main menu was too long, the search 
        options took up more than half of the
        spots on the menu, this design seemed 
        more user-friendly and simple.

Choice: Colors - green files, blue directories 
Reason: I chose to use colors for this to easily
        distinguish the two, I chose blue for 
        directories because that is the default
        on bash.

Choice: Including "PRESS ENTER TO CONTINUE"
Reason: After each operation, I included this
        because without it the menu displays
        again, and this takes the focus from
        the results of the operation.

Choice: Providing search by first letter
        and search by range operations
Reason: I chose to include these because they
        have faster running times than the
        regex search and were simple enough
        for the user to understand easily.

*******************
COLORS
*******************

Colors in this program are designed for bash, if
you want to turn the colors off, please change 
the value of COLOR_ON in include/colors.h to 0 
from 1 and recompile.

*******************
MAKEFILE COMMANDS
*******************

make - compiles and links the test and main programs.

make test - compiles and links the test program.
make main - compiles and links the main program.

make testRun - runs the test program.
make mainRun - runs the main program.

make testValgrindCheck - runs the test program with valgrind.
make mainValgrindCheck - runs the main program with valgrind.

make clean - deletes all the .o files.
make cppChecker - runs cppcheck on all the .c files.

*******************
ADDITIONAL COMMANDS
*******************

sh regenerate - changes the example folder back to its original contents. 
                (Useful after running the program, deleting and moving files).