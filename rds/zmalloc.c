
#include "zmalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include "log.h"


void *zmalloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        return NULL;
    }
    return ptr;
}