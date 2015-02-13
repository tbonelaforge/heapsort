#ifndef _HEAPSORT_H_
#define _HEAPSORT_H_

#include "sortable.h"

void heapsort(Sortable);
void heapify(Sortable);
void sift_down(Sortable, int, int);
int dominates(Sortable, int, int);
int get_dominant_child(Sortable, int, int);
int get_left_child(Sortable, int, int);
int get_right_child(Sortable, int, int);

#endif
