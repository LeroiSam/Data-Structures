Makefile Commands :


make : 

Compiles and links both the maze and test programs

****************MAZE COMMANDS****************

make maze or make mazeLink : 

Compiles and links the maze program


make mazeCompile : 

Compiles the maze program


make mazeValgrindCheck : 

Runs valgrind on the maze program


make mazeRun :

Runs maze program with sample.txt as the argument
To run the maze program with a different argument, the command is : 
./bin/mazeSolver [mazefile]

****************TEST COMMANDS****************

make test or make testLink : 

Compiles and links the test program


make testCompile : 

Compiles the test program


make testValgrindCheck : 

Runs valgrind on the test program


make testRun :

Runs test program

*************ADDITIONAL COMMANDS*************

make clean : 

Removes all the .o files

make cppChecker :

Runs cppcheck on all source code files.
