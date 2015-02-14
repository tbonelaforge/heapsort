#include "sortable.h"

void swap(Sortable self, int i, int j) {
    void * temp = self->elements[i];

    self->elements[i] = self->elements[j];
    self->elements[j] = temp;
}
