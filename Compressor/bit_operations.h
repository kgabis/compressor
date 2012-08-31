//
//  bit_operations.h
//  Compressor
//
//  Created by Krzysztof Gabis on 23.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#ifndef Compressor_bit_operations_h
#define Compressor_bit_operations_h

#define BIT_SET(a,b) ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1<<(b)))
#define BIT_GET(a,b) ((a) & (1<<(b)))

void bits_print_file_bitpattern(const char *filename, size_t offset);
void bits_print_uint(unsigned int num);
void bits_print(int num, int length);
unsigned int bits_count_ones(unsigned long num);

#endif
