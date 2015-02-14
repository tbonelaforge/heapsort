#include <stdio.h>
#include <stdlib.h>

#include "sortheap.h"

struct integer {
    int value;
};

typedef struct integer * Int;

int compare_ints(void * a, void * b) {
    Int a_int = a;
    Int b_int = b;

    if (a_int->value < b_int->value) {
        return -1;
    } else if (a_int->value > b_int->value) {
        return 1;
    } else {
        return 0;
    }
}

void printInt(Int this_int) {
    printf("%d ", this_int->value);
}

void printAsInts(void ** structures, int n) {
    Int * ints = (Int *) structures;
    int i;

    for (i = 0; i < n; i++) {
        printInt(ints[i]);
        printf("\n");
    }
}

Int * makeInts(int * a, int n) {
    int i;
    Int * ints = malloc(n * sizeof(Int));
    Int new_int = NULL;

    if (!ints) {
        return NULL;
    }
    for (i = 0; i < n; i++) {
        new_int = malloc(sizeof(struct integer));
        if (!new_int) {
            return NULL;
        }
        new_int->value = a[i];
        ints[i] = new_int;
    }
    return ints;
}

void test_obvious() {
    printf("About to sort the array: 4, 2, 2, 4, 6, 2\n");

    int a[] = { 4, 2, 2, 4, 6, 2 };
    int n = 6;
    Int * test_ints = makeInts(a, n);
    struct sortable test = {
        (void **) test_ints,
        n,
        &compare_ints
    };

    printf("About to sort test_ints:\n");
    printAsInts(test.elements, test.how_many_elements);
    printf("About to call the heapsort function\n");
    sortheap(&test);
    printf("After sorting the integers, they look like:\n");
    printAsInts(test.elements, test.how_many_elements);
}

void test_pathological0() {
    printf("About to sort the empty array: []\n");
    
    int a[] = { };
    int n = 0;
    Int * test_ints = makeInts(a, n);
    struct sortable test = {
        (void **) test_ints,
        n,
        &compare_ints
    };
    
    printf("About to sort test_integers:\n");
    printAsInts(test.elements, test.how_many_elements);
    printf("About to call the sortheap function\n");
    sortheap(&test);
    printf("After sorting the integers, they look like:\n");
    printAsInts(test.elements, test.how_many_elements);
}

void test_pathological1() {
    printf("About to sort the singleton array: [ 10 ]\n");
    
    int a[] = { 10 };
    int n = 1;
    Int * test_ints = makeInts(a, n);
    struct sortable test = {
        (void **) test_ints,
        n,
        &compare_ints
    };
    
    printf("About to sort test_integers:\n");
    printAsInts(test.elements, test.how_many_elements);
    printf("About to call the sortheap function\n");
    sortheap(&test);
    printf("After sorting the integers, they look like:\n");
    printAsInts(test.elements, test.how_many_elements);
}

void test_pathological28() {
    printf("About to sort an array of 28 ints, already in order\n");
    
    int a[] = { 
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27
    };
    int n = 28;
    Int * test_ints = makeInts(a, n);
    struct sortable test = {
        (void **) test_ints,
        n,
        &compare_ints
    };
    
    printf("About to sort test_integers:\n");
    printAsInts(test.elements, test.how_many_elements);
    printf("About to call the sortheap function\n");
    sortheap(&test);
    printf("After sorting the integers, they look like:\n");
    printAsInts(test.elements, test.how_many_elements);
}

int main() {
    test_obvious();
    test_pathological0();
    test_pathological1();
    test_pathological28();
}
