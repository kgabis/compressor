//
//  bit_stream.h
//  Compressor
//
//  Created by Krzysztof Gabis on 26.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#ifndef Compressor_bit_stream_h
#define Compressor_bit_stream_h

#include <stdio.h>

enum BitStreamType {
    BSTRead = 1,
    BSTWrite = 2
};

typedef struct bs_file_t {
    FILE *fp;
    unsigned char buffer;
    unsigned char bit_offset;
} BS_File;

typedef BS_File * BS_File_Ptr;

BS_File_Ptr bs_open_stream(FILE *file, enum BitStreamType type);
int bs_get_bits(BS_File_Ptr file, unsigned int count);
void bs_put_bits(BS_File_Ptr file, unsigned int bits, unsigned int count);
void bs_put_bit(BS_File_Ptr file, int value);
int bs_get_bit(BS_File_Ptr file);

void bs_close_stream(BS_File_Ptr file);
void bs_test();

#endif
