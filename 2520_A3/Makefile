CC          =	gcc
# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-Wall -ansi -pedantic -g
LDFLAGS     =

#Directories where the compiler can find things
INCLUDES    = -Iinclude
LIBDIRS     = 
LIBS        = 

# add directory names here if you want to separate files by directories
BINDIR = bin/
SRCDIR = src/

#Put the names of your source code file in the lines below.  

MAINSOURCE = $(SRCDIR)main.c $(SRCDIR)tree.c $(SRCDIR)files.c $(SRCDIR)search.c $(SRCDIR)delete.c $(SRCDIR)colors.c $(SRCDIR)rename.c $(SRCDIR)move.c $(SRCDIR)fileTree.c
TESTSOURCE = $(SRCDIR)test.c $(SRCDIR)tree.c $(SRCDIR)colors.c

#The list of object files is below.  The object file names here must match the file names of your source code 
# except with .o instead of .c.   Make changes as appropriate


MAINOBJS    = main.o tree.o files.o search.o delete.o colors.o rename.o move.o fileTree.o
TESTOBJS	= test.o tree.o colors.o

#The names of the binary programs that will be produced.  
#
MAINPROGNAME = $(BINDIR)main
TESTPROGNAME = $(BINDIR)test

#The arguments passed to the files when being run.
#

MAINARGS = example
TESTARGS = 

#Tags for valgrind
#

VALGRINDTAGS = --leak-check=full --show-reachable=yes

default: mainLink testLink

#main functions

main: mainLink
	

mainLink: mainCompile
	$(CC) $(LIBDIRS) $(LDFLAGS) -o $(MAINPROGNAME) $(MAINOBJS) $(LIBS)

mainCompile: 
	$(CC) $(CFLAGS) -c $(MAINSOURCE) $(INCLUDES)

mainValgrindCheck: 
	valgrind $(VALGRINDTAGS) $(MAINPROGNAME) $(MAINARGS)

mainRun:
	$(MAINPROGNAME) $(MAINARGS)

#test functions

test: testLink
	

testLink: testCompile
	$(CC) $(LIBDIRS) $(LDFLAGS) -o $(TESTPROGNAME) $(TESTOBJS) $(LIBS)

testCompile:
	$(CC) $(CFLAGS) -c $(TESTSOURCE) $(INCLUDES)

testValgrindCheck: 
	valgrind $(VALGRINDTAGS) $(TESTPROGNAME) $(TESTARGS)

testRun:
	$(TESTPROGNAME) $(TESTARGS)

#general functions

clean:
	@ rm *.o

cppChecker:
	cppcheck $(MAINSOURCE) $(TESTSOURCE)
