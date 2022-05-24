all:output

output:echo_file.o
	gcc -o output echo_file.o

echo_file.o:echo_file.c
	gcc -c -g -Wall echo_file.c


clean:
	rm -f *.o output
