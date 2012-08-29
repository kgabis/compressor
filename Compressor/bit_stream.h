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

enum BitStreamStatus {
    BSSClosed = 1,
    BSSOpen = 2
};

typedef struct bit_stream_t {
    FILE *fp;
    unsigned char buffer;
    unsigned char bit_offset;
    enum BitStreamStatus status;
} Bit_Stream;

typedef Bit_Stream * Bit_Stream_Ptr;

Bit_Stream_Ptr bs_open_stream(FILE *file, enum BitStreamType type);
int bs_get_bits(Bit_Stream_Ptr stream, unsigned int count);
void bs_put_bits(Bit_Stream_Ptr stream, unsigned int bits, unsigned int count);
void bs_put_bit(Bit_Stream_Ptr stream, int value);
int bs_get_bit(Bit_Stream_Ptr stream);

void bs_close_stream(Bit_Stream_Ptr stream);
void bs_test();

#endif
