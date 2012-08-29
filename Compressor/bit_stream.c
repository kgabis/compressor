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

void bs_test() {
    const char filename[] = "/users/kgabis/code/objc/mine/Compressor/bs_test.txt";
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL){
       puts("Error: Wrong filename.");
    }
    Bit_Stream_Ptr bit_stream = bs_open_stream(fp, BSTWrite);
    bs_put_bits(bit_stream, 0x4, 4);
    bs_put_bits(bit_stream, 0x1, 2);
    bs_close_stream(bit_stream);
    fclose(fp);
    fp = fopen(filename, "rb");
    bit_stream = bs_open_stream(fp, BSTRead);
    int c;
    while ((c = bs_get_bits(bit_stream, 2)) != EOF) {
        bits_print(c, 2);
        printf("\n");
    }    
    fclose(fp);
}

Bit_Stream_Ptr bs_open_stream(FILE *file, enum BitStreamType type) {
    Bit_Stream_Ptr new_stream = (Bit_Stream_Ptr)malloc(sizeof(Bit_Stream));
    new_stream->fp = file;
    if (type == BSTRead) {
        new_stream->bit_offset = 8;
    } else {
        new_stream->bit_offset = 0;
    }
    new_stream->status = BSSOpen;
    return new_stream;
}

int bs_get_bit(Bit_Stream_Ptr stream) {
    if (stream->bit_offset == 8) {
        int c;
        c = fgetc(stream->fp);
        if (c == EOF) {
            return EOF;
        }
        stream->buffer = c;
        stream->bit_offset = 0;
    }
    int output = BIT_GET(stream->buffer, 7 - stream->bit_offset);
    stream->bit_offset++;
    return output;
}

int bs_get_bits(Bit_Stream_Ptr stream, unsigned int count) {
    int output = 0;
    int i;
    int c;
    for (i = 0; i < count; i++) {
        c = bs_get_bit(stream);
        if (c == EOF) {
            output = EOF;
        } else if (c) {
            BIT_SET(output, count - i - 1);
        } else {
            BIT_CLEAR(output, count - i - 1);
        }
    }
    return output;
}

void bs_put_bit(Bit_Stream_Ptr stream, int value) {
    unsigned char val = !!value;
    if (val) {
        BIT_SET(stream->buffer, 7 - stream->bit_offset);
    } else {
        BIT_CLEAR(stream->buffer, 7 - stream->bit_offset);
    }
    stream->bit_offset++;
    if (stream->bit_offset > 7) {
        fputc(stream->buffer, stream->fp);
        stream->buffer = 0;
        stream->bit_offset = 0;
    }
}

void bs_put_bits(Bit_Stream_Ptr stream, unsigned int bits, unsigned int count) {
    int i;
    for (i = 0; i < count; i++) {
        bs_put_bit(stream, BIT_GET(bits, count - i - 1));
    }
}

void bs_close_stream(Bit_Stream_Ptr stream) {
    while (stream->bit_offset != 0) {
        bs_put_bit(stream, 0);
    }
    stream->status = BSSClosed;
}