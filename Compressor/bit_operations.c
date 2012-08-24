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

void bits_print(unsigned int num, unsigned int mask) {
    //bits_print_uint(mask);
    while (BIT_GET(mask, 0)) {
        if (BIT_GET(num, 0)) {
            printf("1");
        } else {
            printf("0");
        }
        mask = mask >> 1;
    }
    printf("\n");
}