nodl: nodl.c matmul.so
	gcc -o nodl nodl.c matmul.so

dl: dl.c
	gcc -o dl -rdynamic dl.c -ldl

lib: matmul.c matmul.h
	gcc -shared -fpic -o matmul.so matmul.c

clean:
	rm matmul.so dl nodl