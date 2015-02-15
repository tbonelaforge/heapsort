#include <stdio.h>
#include <stdlib.h>

#include "sortable.h"
#include "sortheap.h"

struct Results {
    int * C;
    int L;
};

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

void destroyInts(Int * ints, int how_many_ints) {
    int i;

    for (i = 0; i < how_many_ints; i++) {
        free(ints[i]);
    }
}

Sortable make_sortable_ints(int A[], int N) {
    Int * elements;
    Sortable self;

    elements = makeInts(A, N);
    if (!elements) {
        return NULL;
    }
    self = malloc(sizeof(struct sortable));
    if (!self) {
        destroyInts(elements, N);
        return NULL;
    }
    self->elements = (void **) elements;
    self->how_many_elements = N;
    self->comp = &compare_ints;
    return self;
}

void destroy_sortable_ints(Sortable self) {
    destroyInts((Int *) self->elements, self->how_many_elements);
    free(self);
}

int * make_divisor_counts(int max_value) {
    int * divisor_counts = malloc((max_value + 1) * sizeof(int));
    int i;

    if (!divisor_counts) {
        return NULL;
    }
    for (i = 0; i <= max_value; i++) {
        divisor_counts[i] = -1;
    }
    return divisor_counts;
}

void initialize_divisor_counts(int * divisor_counts, int A[], int N) {
    int i;

    for (i = 0; i < N; i++) {
        divisor_counts[A[i]] = 0;
    }
}

void print_divisor_counts(int * divisor_counts, int max_value) {
    int i;
    for (i = 0; i <= max_value; i++) {
        printf("%d", divisor_counts[i]);
        if (i < max_value) {
            printf(", ");
        }
    }
}

int find_last_repeated_element(Sortable self, int i) {
    Int this_int = self->elements[i];
    int j = i + 1;
    int comparison;

    while (j < self->how_many_elements) {
        comparison = (*self->comp)(this_int, self->elements[j]);
        if (comparison != 0) {
            break;
        }
        j += 1;
    }
    return j - 1;
}

void accumulate_divisor_counts(int value, int how_many_values, int * divisor_counts, int max_value) {
    int k = 2;
    int multiple;

    divisor_counts[value] += how_many_values - 1;
    while ((multiple = k * value) <= max_value) {
        if (divisor_counts[multiple] > -1) {
            divisor_counts[multiple] += how_many_values;
            
        }
        k += 1;
    }
}

struct Results * fill_results(struct Results * results, int A[], int N, int * divisor_counts) {
    int * C;
    int i;
    int non_divisors;

    C = malloc(N * sizeof(int));
    if (!C) {
        return NULL;
    }
    results->C = C;
    results->L = N;
    for (i = 0; i < N; i++) {
        non_divisors = N - 1 - divisor_counts[A[i]];
        results->C[i] = non_divisors;
    }
    return results;
}

struct Results solution(int A[], int N) {
    struct Results results;
    Sortable self = make_sortable_ints(A, N);
    Int element;
    int max_value;
    int * divisor_counts;
    int i;
    int j;
    int value;
    int how_many_values;

    sortheap(self);
    element = self->elements[N - 1];
    max_value = element->value;
    divisor_counts = make_divisor_counts(max_value);
    initialize_divisor_counts(divisor_counts, A, N);
    for (i = 0; i < N; i++) {
        j = find_last_repeated_element(self, i);
        element = self->elements[j];
        value = element->value;
        how_many_values = j - i + 1;
        accumulate_divisor_counts(
                                  value,
                                  how_many_values,
                                  divisor_counts,
                                  max_value
                                  );
        i = j;
    }
    fill_results(&results, A, N, divisor_counts);
    destroy_sortable_ints(self);
    free(divisor_counts);
    return results;
}

void print_result(struct Results r) {
    int i;

    for (i = 0; i < r.L; i++) {
        printf("%d\n", r.C[i]);
    }
}

int main() {
    printf("ABout to try and count non-divisors of :\n");
    printf("3, 1, 2, 3, 6\n");

    int A[] = { 3, 1, 2, 3, 6 };
    int N = 5;
    struct Results r = solution(A, N);
    printf("Successfully computed a solution, and the result is:\n");
    print_result(r);
}
