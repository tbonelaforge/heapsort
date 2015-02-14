all: sortheap_test.bin

sortheap_test.bin: sortheap_test.c sortheap.o sortable.o sortheap.h sortable.h
	gcc -I ./ sortheap_test.c sortheap.o sortable.o -o sortheap_test.bin

sortheap.o: sortheap.c sortheap.h sortable.h
	gcc -I ./ -c sortheap.c

sortable.o: sortable.c sortable.h
	gcc -I ./ -c sortable.c
