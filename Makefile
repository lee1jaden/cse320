as6 : as6.c as6.h
	gcc -g -o as6 ./as6.c ./as6.h -pthread

clean : 
	rm ./as6