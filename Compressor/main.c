//
//  main.c
//  Compressor
//
//  Created by Krzysztof Gabis on 22.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "bit_operations.h"
#include "priority_queue.h"
//#define BIT_SET(byte, ix, val) (byte = (byte & ~(!val << ix)) | (val << ix))
//#define BIT_GET(byte, ix) ((byte >> ix) & 1u)




int main(int argc, const char * argv[])
{
    PQueue_Ptr pqueue = pqueue_init();
    char string1[] = "string1";
    char string2[] = "string2";
    char string3[] = "string3";
    pqueue_enqueue(pqueue, (void*)string1, 10);
    pqueue_enqueue(pqueue, (void*)string2, 1);
    pqueue_enqueue(pqueue, (void*)string3, 4);
    char *string_ptr;
    while ((string_ptr = pqueue_dequeue(pqueue)) != NULL) {
        printf("%s\n", string_ptr);
    }
    // insert code here...
    printf("\n");
    return 0;
}



