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

typedef struct bs_fp_t {
    FILE fp;
    unsigned char byte_buffer;
    unsigned char buffer_index;
} BS_File;

typedef BS_File * BS_File_Ptr;

BS_File_Ptr bs_open_file(const char *filename);
int bs_get_bits(BS_File_Ptr file, unsigned int count);
void bs_put_bits(BS_File_Ptr file, unsigned int bits, unsigned int count);
void bs_close_file(BS_File_Ptr file);

#endif
