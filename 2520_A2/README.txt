DYLAN COOPER
0839116


Notes To Marker : 

Recursive functions -- In listPlus.c, add_to_sorted_list and 
search_through_sorted_list are recursive function that 
implement binary sorting and searching as add-ons for my 
linked list implementation.

Collision resolution -- There is an array of sorted linked 
lists with indices that match the hash value from the key, 
if there is a collision in the hash function, both of them 
will be in the linked list.

Sorting lists -- The full list of names is sorted by last 
name (then first name and phone number) alphabetically and
the lists in the table are sorted only by phone number.

Make Functions :


*****COMPILING FUNCTIONS*****


make

Compiles and links both phone and test programs.

make phone, make test

Compiles and links phone and test respectively.


*****RUNNING FUNCTIONS*****


make phoneRun, make testRun

Runs phone program (with input.csv as command line argument) and test program respectively.


*****ADDITIONAL FUNCTIONS*****


make phoneValgrindCheck, make testValgrindCheck

Runs phone program and test program respectively under valgrind.

make cppChecker

Runs cppcheck on all the .c files.

make clean

Removes all .o files.