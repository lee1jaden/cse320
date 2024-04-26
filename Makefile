as7 : as7.c as7.h
	gcc -g -o as7 ./as7.c ./as7.h -pthread

clean : 
	rm ./as7