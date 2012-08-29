//
//  bit_operations.c
//  Compressor
//
//  Created by Krzysztof Gabis on 23.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include "bit_operations.h"

void bits_print_uint(unsigned int num) {
    int i;
    for (i = 0; i < (sizeof(unsigned int) * 8); i++) {
        if(BIT_GET(num, (sizeof(unsigned int) * 8) - 1)) {
            printf("1");
        } else {
            printf("0");
        }
        num = num << 1;
    }
    printf("\n");
}

void bits_print(int num, int length) {
    int i;
    for (i = 0; i < length; i++) {
        if (BIT_GET(num, length - 1 - i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
}

unsigned int bits_count_ones(unsigned long num) {
    int count = 0;
    int i;
    for (i = 0; i < sizeof(unsigned long); i++) {
        if (BIT_GET(num, i)) {
            count++;
        }
    }
    return count;
}