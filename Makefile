CC = gcc
CFLAGS = -g -Wall -I.

as8 : ./as8.o ./wrappers.o
	$(CC) $(CFLAGS) -o ./as8 ./as8.o ./wrappers.o

as8.o : ./as8.c ./as8.h
	$(CC) $(CFLAGS) -c ./as8.c -pthread

wrappers.o : ./wrappers.h ./wrappers.c
	$(CC) $(CFLAGS) -c ./wrappers.c 

clean : 
	rm ./as8 ./*.o