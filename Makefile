all: quicksort_test.bin disc_intersections.bin

heapsort_test.bin: heapsort_test.c heapsort.o heapsort.h sortable.h sort_util.o
	gcc -I ./ heapsort_test.c heapsort.o sort_util.o -o heapsort_test.bin

heapsort.o: heapsort.c heapsort.h sortable.h sort_util.h
	gcc -I ./ -c heapsort.c

sort_util.o: sort_util.c sort_util.h
	gcc -I ./ -c sort_util.c
