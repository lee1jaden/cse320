CC = gcc
CFLAGS = -g -Wall -I.

[executable] : [object files]
	$(CC) $(CFLAGS) -o [executable name] [object files]

[object file] : [source file] [header file]
	$(CC) $(CFLAGS) -c [source file]

clean : 
	rm [executable] ./*.o