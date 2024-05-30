nodl:
	gcc -o nodl nodl.c matmul.so
dl:
	gcc -o dl -rdynamic dl.c -ldl
lib:    
	gcc -shared -fpic -o matmul.so matmul.c
clean:
	rm matmul.so dl nodl
