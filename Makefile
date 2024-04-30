as7_pc : as7_pc.c
	gcc -g -o as7_pc ./as7_pc.c -pthread

as7_rw : as7_rw.c
	gcc -g -o as7_rw ./as7_rw.c -pthread

clean : 
	rm ./as7_pc ./as7_rw
	