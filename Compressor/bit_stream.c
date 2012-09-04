//
//  bit_stream.c
//  Compressor
//
//  Created by Krzysztof Gabis on 26.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "bit_stream.h"
#include "bit_operations.h"
#include "compressor.h"

#define BUFFER_SIZE sizeof(unsigned int) * 8

Bit_Stream_Ptr bs_open_stream(FILE *file, enum BitStreamType type) {
    Bit_Stream_Ptr new_stream = (Bit_Stream_Ptr)malloc(sizeof(Bit_Stream));
    new_stream->fp = file;
    if (type == BSTRead) {
        new_stream->bit_offset = BUFFER_SIZE;
    } else {
        new_stream->bit_offset = 0;
    }
    new_stream->status = BSSOpen;
    return new_stream;
}

int inline bs_get_bit(Bit_Stream_Ptr stream) {
    if (stream->bit_offset == BUFFER_SIZE) {
        if (feof(stream->fp)) {
            return EOF;
        }
        fread(&stream->buffer, 1, sizeof(stream->buffer), stream->fp);
        stream->bit_offset = 0;
    }
    int output = BIT_GET(stream->buffer, BUFFER_SIZE - 1 - stream->bit_offset);
    stream->bit_offset++;
    return output;
}

int inline bs_get_bits(Bit_Stream_Ptr stream, unsigned int length) {
    int output = 0;
    int i;
    int c;
    for (i = 0; i < length; i++) {
        c = bs_get_bit(stream);
        if (c == EOF) {
            output = EOF;
        } else if (c) {
            BIT_SET(output, length - i - 1);
        } else {
            BIT_CLEAR(output, length - i - 1);
        }
    }
    return output;
}

void inline bs_put_bit(Bit_Stream_Ptr stream, int value) {
    if (value) {
        BIT_SET(stream->buffer, BUFFER_SIZE - 1 - stream->bit_offset);
    } else {
        BIT_CLEAR(stream->buffer, BUFFER_SIZE - 1 - stream->bit_offset);
    }
    stream->bit_offset++;
    if (stream->bit_offset > BUFFER_SIZE - 1) {
        fwrite(&stream->buffer, 1, sizeof(stream->buffer), stream->fp);
        stream->buffer = 0;
        stream->bit_offset = 0;
    }
}

void inline bs_put_bits(Bit_Stream_Ptr stream, unsigned int bits, unsigned int length) {
    while (length--) {
        bs_put_bit(stream, BIT_GET(bits, length));

    }
}

void bs_close_stream(Bit_Stream_Ptr stream) {
    while (stream->bit_offset != 0) {
        bs_put_bit(stream, 0);
    }
    stream->status = BSSClosed;
}