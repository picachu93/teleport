CC = gcc
CFLAGS = -g -Wall -std=c99
all: spacemst 
spacemst: spacemst.o
	$(CC) $(CFLAGS) -o spacemst spacemst.o
spacemst.o: spacemst.c
	$(CC) $(CFLAGS) -c spacemst.c
clean: 
	$(RM) $(all)
