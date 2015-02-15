all: sortheap_test.bin count_non_divisors.bin codility_version.bin

sortheap_test.bin: sortheap_test.c sortheap.o sortable.o sortheap.h sortable.h
	gcc -I ./ sortheap_test.c sortheap.o sortable.o -o sortheap_test.bin

count_non_divisors.bin: count_non_divisors.c sortheap.o sortheap.h sortable.h
	gcc -I ./ count_non_divisors.c sortheap.o sortable.o -o count_non_divisors.bin

codility_version.bin: codility_version.c
	gcc codility_version.c -o codility_version.bin

sortheap.o: sortheap.c sortheap.h sortable.h
	gcc -I ./ -c sortheap.c

sortable.o: sortable.c sortable.h
	gcc -I ./ -c sortable.c
