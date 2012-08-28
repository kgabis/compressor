//
//  priority_queue.h
//  Compressor
//
//  Created by Krzysztof Gabis on 24.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#ifndef Compressor_priority_queue_h
#define Compressor_priority_queue_h

typedef int (*Compare_Function)(const void *a, const void *b);

struct pqueue_t {
    void **items;
    unsigned int _capacity;
    unsigned int count;
    Compare_Function a_less_b;
};

typedef struct pqueue_t PQueue;
typedef PQueue * PQueue_Ptr;

PQueue_Ptr pqueue_init(Compare_Function compare);
void pqueue_enqueue(PQueue_Ptr queue, void *item);
void * pqueue_dequeue(PQueue_Ptr queue);
void pqueue_dealloc(PQueue_Ptr queue);

#endif
