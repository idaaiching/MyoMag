# makefile for “MyoMag-project"

CC=gcc -Wall
RM=rm -f
CFLAGS=-Wall -g 
LDFLAGS= -lcunit

SRCDIR= src
TESTDIR= test
PYTHONDIR= -L/usr/include/python2.7
INC=-I$(SRCDIR) -I$(TESTDIR) -I$(PYTHONDIR)

OBJS= AccelerationMagnitude.o DataLoader.o
TESTS= DataLoader_test.o AccelerationMagnitude_test.o

%.o :	$(SRCDIR)/%.c
	$(CC) -c $^ -o $@ $(INC)


%.o :	$(TESTDIR)/%.c
	$(CC) -c $< -o $@ $(INC)

myomag:	$(OBJS) main.o
	$(CC) -o $@ $^ $(INC)

dataloader_test: DataLoader_test.o $(OBJS) 
	$(CC) -L/usr/local/lib -o $@ $^ $(INC) $(LDFLAGS)

accelerationmagnitude_test: AccelerationMagnitude_test.o $(OBJS) 
	$(CC) -L/usr/local/lib -o $@ $^ $(INC) $(LDFLAGS)

report :
	xsltproc -novalid cunit-to-junit.xsl CUnitAutomated-Results.xml > myomag_TestResults.xml

.PHONY : runtests
runtests : dataloader_test accelerationmagnitude_test
		./dataloader_test

.PHONY : all
all : myomag dataloader_test accelerationmagnitude_test

.PHONY : clean
clean :
	$(RM) myomag
	$(RM) accelerationmagnitude_test
	$(RM) dataloader_test
	$(RM) *.o
