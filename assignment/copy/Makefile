all:output

output:copy_file.o
	gcc -o output copy_file.o

copy_file.o:copy_file.c
	gcc -c -g -Wall copy_file.c


clean:
	rm -f test_cp.o output

