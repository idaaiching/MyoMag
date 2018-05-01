# makefile for “MyoMag-project"

CC=gcc -Wall
RM=rm -f
CFLAGS=-Wall -g 
LDFLAGS= -lcunit

SRCDIR= src
TESTDIR= test
PYTHONDIR= -L/usr/include/python2.7
INC=-I$(SRCDIR) -I$(TESTDIR) -I$(PYTHONDIR)

OBJS= acc.o DataLoader.o
TESTS=acc_test.o

%.o :	$(SRCDIR)/%.c
	$(CC) -c $^ -o $@ $(INC)


%.o :	$(TESTDIR)/%.c
	$(CC) -c $< -o $@ $(INC)

myomag:	$(OBJS) main.o
	$(CC) -o $@ $^ $(INC)

myomag_test:	$(TESTS) $(OBJS) 
	$(CC) -L/usr/local/lib -o $@ $^ $(INC) $(LDFLAGS)

report :
	xsltproc -novalid cunit-to-junit.xsl CUnitAutomated-Results.xml > myomag_TestResults.xml

.PHONY : runtests
runtests : myomag_test
		./$<

.PHONY : all
all : myomag myomag_test

.PHONY : clean
clean :
	(RM) myomag
	(RM) tests
	(RM) CUnit*.xml
	(RM) myomag_TestResults.xml.xml
	(RM) *.o
	(RM) *~
	(RM) src/*~
	(RM) test/*~