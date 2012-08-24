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

enum {
    PQStartingSize = 256
};

PQueue_Ptr pqueue_init() {
    PQueue_Ptr new_queue = (PQueue_Ptr)malloc(sizeof(PQueue));
    assert(new_queue != NULL);
    new_queue->items = (PQueue_Item*)malloc(sizeof(PQueue_Item) * PQStartingSize);
    assert(new_queue->items != NULL);
    new_queue->length = PQStartingSize;
    new_queue->used = 0;
    return new_queue;
}

void pqueue_enqueue(PQueue_Ptr queue, const void *value, unsigned int priority) {
    queue->items[queue->used].value = value;
    queue->items[queue->used].priority = priority;
    queue->used++;
}

void * pqueue_dequeue(PQueue_Ptr queue) {
    PQueue_Item min;
    min.priority = ~0u;
    if (queue->used == 1) {
        queue->used--;
        return (void*)queue->items[0].value;
    } else if (queue->used == 0) {
        return NULL;
    }
    int i;
    int min_i;
    for (i = 0; i < queue->used; i++) {
        if (queue->items[i].priority < min.priority) {
            min = queue->items[i];
            min_i = i;
        }
    }
    queue->items[min_i] = queue->items[queue->used - 1];
    queue->used--;
    return (void*)min.value;
}

void pqueue_dealloc(PQueue_Ptr queue) {
    
}
