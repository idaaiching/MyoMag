# makefile for "C-project"

CC = gcc
RM = rm -f
CFLAGS = -Wall -g 
#LDFLAGS = -lm

final	: main.o acc.o readcsv.o
		$(CC) $(LDFLAGS) -o $@ $^

main.o	: main.c
		$(CC) $(LDFLAGS) -o $@ -c $<

acc.o	: acc.c
		$(CC) $(LDFLAGS) -o $@ -c $<
readcsv.o: readcsv.o
		$(CC) $(LDFLAGS) -o $@ -c $<

.PHONY	: clean
clean	:
		$(RM) final