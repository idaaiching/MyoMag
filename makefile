# makefile for “MyoAcc-project"

CC=gcc -Wall
RM=rm -f
CFLAGS=-Wall -g 
LDFLAGS= -lcunit

SRCDIR= src
TESTDIR= test
INC=-I$(SRCDIR) -I$(TESTDIR) #-I$(HOME)/include

OBJS= acc.o #readcsv.o
TESTS=acc_test.o

%.o :	$(SRCDIR)/%.c
	$(CC) -c $^ -o $@ $(INC)


%.o :	$(TESTDIR)/%.c
	$(CC) -c $< -o $@ $(INC)

MyoAcc:	$(OBJS) main.o
	$(CC) -o $@ $^ $(INC)

MyoAcc_test:	$(TESTS) $(OBJS) 
	$(CC) -L/usr/local/lib -o $@ $^ $(INC) $(LDFLAGS)

report :
	xsltproc -novalid cunit-to-junit.xsl CUnitAutomated-Results.xml > MyoAcc_TestResults.xml

.PHONY : runtests
runtests : MyoAcc_test
		./$<

.PHONY : all
all : MyoAcc MyoAcc_test

.PHONY : clean
clean :
	(RM) MyoAcc
	(RM) tests
	(RM) CUnit*.xml
	(RM) MyoAcc_TestResults.xml.xml
	(RM) *.o
	(RM) *~
	(RM) src/*~
	(RM) test/*~