//
//  bit_operations.c
//  Compressor
//
//  Created by Krzysztof Gabis on 23.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "bit_stream.h"
#include "bit_operations.h"

void print_file_bitpattern(const char *filename, size_t offset) {
    FILE *fp = fopen(filename, "rb");
    fseek(fp, offset, SEEK_SET);
    Bit_Stream_Ptr stream = bs_open_stream(fp, BSTRead);
    int c;
    int i = 1;
    while ((c = bs_get_bit(stream)) != EOF) {
        if (i%9 == 0) {
            printf("\n");
            i = 1;
        }
        if (c) {
            printf("1");
        } else {
            printf("0");
        }
        i++;
        
    }
    bs_close_stream(stream);
    fclose(fp);
}

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