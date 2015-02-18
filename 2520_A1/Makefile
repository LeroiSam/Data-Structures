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

MAZESOURCE = $(SRCDIR)main.c $(SRCDIR)coordADT.c $(SRCDIR)list.c $(SRCDIR)stack.c $(SRCDIR)maze.c
TESTSOURCE = $(SRCDIR)test.c $(SRCDIR)list.c $(SRCDIR)stack.c $(SRCDIR)coordADT.c

#The list of object files is below.  The object file names here must match the file names of your source code 
# except with .o instead of .c.   Make changes as appropriate


MAZEOBJS    = main.o coordADT.o list.o stack.o maze.o
TESTOBJS	= test.o list.o stack.o coordADT.o

#The names of the binary programs that will be produced.  
#
MAZEPROGNAME = $(BINDIR)mazeSolver
TESTPROGNAME = $(BINDIR)stackTest

#The arguments passed to the files when being run.
#

MAZEARGS = sample.txt
TESTARGS = 

#Tags for valgrind
#

VALGRINDTAGS = --leak-check=full --show-reachable=yes

default: mazeLink testLink

#maze functions

maze: mazeLink


mazeLink: mazeCompile
	$(CC) $(LIBDIRS) $(LDFLAGS) -o $(MAZEPROGNAME) $(MAZEOBJS) $(LIBS)

mazeCompile: 
	$(CC) $(CFLAGS) -c $(MAZESOURCE) $(INCLUDES)

mazeValgrindCheck: 
	valgrind $(VALGRINDTAGS) $(MAZEPROGNAME) $(MAZEARGS)

mazeRun:
	$(MAZEPROGNAME) $(MAZEARGS)

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
	cppcheck $(MAZESOURCE) $(TESTSOURCE)
