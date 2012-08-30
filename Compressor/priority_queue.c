//
//  priority_queue.c
//  Compressor
//
//  Created by Krzysztof Gabis on 24.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"
#include "assert.h"
#include "compressor.h"

enum {
    PQStartingSize = CPSMaxLeafVal
};

PQueue_Ptr pqueue_init(Compare_Function compare_function) {
    PQueue_Ptr new_queue = (PQueue_Ptr)malloc(sizeof(PQueue));
    new_queue->items = (void**)malloc(PQStartingSize * sizeof(void*));
    new_queue->capacity = PQStartingSize;
    new_queue->count = 0;
    new_queue->a_less_b = compare_function;
    return new_queue;
}

void pqueue_enqueue(PQueue_Ptr queue, void *item) {
    if (queue->count >= queue->capacity) {
        queue->capacity = queue->capacity * 2;
        queue->items = realloc(queue->items, queue->capacity);
    }
    queue->items[queue->count] = item;
    queue->count++;
}

void * pqueue_dequeue(PQueue_Ptr queue) {
    if (queue->count == 0) {
        return NULL;
    }
    int min_index = 0;
    void *min_item = queue->items[min_index];
    int i;
    for (i = min_index; i < queue->count; i++) {
        if (queue->a_less_b(queue->items[i], min_item)) {
            min_item = queue->items[i];
            min_index = i;
        }
    }
    queue->items[min_index] = queue->items[queue->count - 1];
    queue->count--;
    return min_item;
}

void pqueue_dealloc(PQueue_Ptr queue) {
    free(queue->items);
    free(queue);
}
