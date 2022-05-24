all:output

output: cat_file.o
	gcc -o output cat_file.o

cat_file.o: cat_file.c
	gcc -c -g -Wall cat_file.c


clean:
	rm -f *.o output
