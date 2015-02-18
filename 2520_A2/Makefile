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

phoneSOURCE = $(SRCDIR)main.c $(SRCDIR)listing.c $(SRCDIR)list.c $(SRCDIR)table.c $(SRCDIR)listPlus.c $(SRCDIR)phoneBook.c
TESTSOURCE = $(SRCDIR)test.c $(SRCDIR)listing.c $(SRCDIR)list.c $(SRCDIR)table.c $(SRCDIR)listPlus.c $(SRCDIR)phoneBook.c

#The list of object files is below.  The object file names here must match the file names of your source code 
# except with .o instead of .c.   Make changes as appropriate


phoneOBJS    = main.o listing.o list.o table.o listPlus.o phoneBook.o
TESTOBJS	= test.o list.o listPlus.o table.o listing.o phoneBook.o

#The names of the binary programs that will be produced.  
#
PHONEPROGNAME = $(BINDIR)phone
TESTPROGNAME = $(BINDIR)test

#The arguments passed to the files when being run.
#

phoneARGS = input.csv
TESTARGS = 

#Tags for valgrind
#

VALGRINDTAGS = --leak-check=full --show-reachable=yes

default: phoneLink testLink

#phone functions

phone: phoneLink


phoneLink: phoneCompile
	$(CC) $(LIBDIRS) $(LDFLAGS) -o $(PHONEPROGNAME) $(phoneOBJS) $(LIBS)

phoneCompile: 
	$(CC) $(CFLAGS) -c $(phoneSOURCE) $(INCLUDES)

phoneValgrindCheck: 
	valgrind $(VALGRINDTAGS) $(PHONEPROGNAME) $(phoneARGS)

phoneRun:
	$(PHONEPROGNAME) $(phoneARGS)

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
	cppcheck $(phoneSOURCE) $(TESTSOURCE)
