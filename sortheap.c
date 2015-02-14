
#include "sortheap.h"
#include "sortable.h"

void sortheap(Sortable self) {
    int unsorted;

    heapify(self);
    unsorted = self->how_many_elements;
    while (unsorted) {
        swap(self, 0, unsorted - 1);
        unsorted -= 1;
        sift_down(self, 0, unsorted);
    }
}

void heapify(Sortable self) {
    int start = self->how_many_elements - 1;

    while (start >= 0) {
        sift_down(self, start, self->how_many_elements);
        start -= 1;
    }
}

void sift_down(Sortable self, int start, int n) {
    int child;

    while (!dominates(self, start, n)) {
        child = get_dominant_child(self, start, n);
        swap(self, start, child);
        start = child;
    }
}

int dominates(Sortable self, int start, int n) {
    int dominant_child = get_dominant_child(self, start, n);
    int comparison;

    if (dominant_child < 0) {
        return 1;
    }
    comparison = (*self->comp)(self->elements[start], self->elements[dominant_child]);
    return ( comparison >= 0 ) ? 1 : 0;
}

int get_dominant_child(Sortable self, int start, int n) {
    int left = get_left_child(self, start, n);
    int right = get_right_child(self, start, n);
    int comparison;

    if (left < 0 && right < 0) {
        return -1;
    }
    if (left >= 0 && right < 0) {
        return left;
    }
    if (left < 0 && right >= 0) {
        return right;
    }
    comparison = (*self->comp)(self->elements[left], self->elements[right]);
    return ( comparison >= 0 ) ? left : right;
}

int get_left_child(Sortable self, int start, int n) {
    int left = 2 * start + 1;

    return ( left < n ) ? left : -1;
}

int get_right_child(Sortable self, int start, int n) {
    int right = 2 * start + 2;

    return ( right < n ) ? right : -1;
}
