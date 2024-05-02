CC = gcc
CFLAGS = -g -I.

as7_pc : ./as7_pc.o ./wrappers.o
	$(CC) $(CFLAGS) -o as7_pc ./as7_pc.o ./wrappers.o

as7_pc.o : ./as7_pc.c ./as7_pc.h
	$(CC) $(CFLAGS) -c ./as7_pc.c -pthread

as7_rw : ./as7_rw.o ./wrappers.o
	$(CC) $(CFLAGS) -o as7_rw ./as7_rw.c ./wrappers.o

as7_rw.o : ./as7_rw.c ./as7_rw.h
	$(CC) $(CFLAGS) -c ./as7_rw.c -pthread

wrappers.o : ./wrappers.h ./wrappers.c
	$(CC) $(CFLAGS) -c ./wrappers.c 

clean : 
	rm ./as7_pc ./as7_rw ./*.o
	