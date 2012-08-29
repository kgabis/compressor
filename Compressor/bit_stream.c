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
    BS_File_Ptr bs_file = bs_open_stream(fp, BSTWrite);
    bs_put_bits(bs_file, 0x4, 4);
    bs_put_bits(bs_file, 0x1, 2);
    bs_close_stream(bs_file);
    fclose(fp);
    fp = fopen(filename, "rb");
    bs_file = bs_open_stream(fp, BSTRead);
    int c;
    while ((c = bs_get_bits(bs_file, 2)) != EOF) {
        bits_print(c, 2);
        printf("\n");
    }    
    fclose(fp);
}

BS_File_Ptr bs_open_stream(FILE *file, enum BitStreamType type) {
    BS_File_Ptr new_bsfile = (BS_File_Ptr)malloc(sizeof(BS_File));
    new_bsfile->fp = file;
    if (type == BSTRead) {
        new_bsfile->bit_offset = 8;
    } else {
        new_bsfile->bit_offset = 0;
    }
    return new_bsfile;
}

int bs_get_bit(BS_File_Ptr file) {
    if (file->bit_offset == 8) {
        int c;
        c = fgetc(file->fp);
        if (c == EOF) {
            return EOF;
        }
        file->buffer = c;
        file->bit_offset = 0;
    }
    int output = BIT_GET(file->buffer, 7 - file->bit_offset);
    file->bit_offset++;
    return output;
}

int bs_get_bits(BS_File_Ptr file, unsigned int count) {
    int output = 0;
    int i;
    int c;
    for (i = 0; i < count; i++) {
        c = bs_get_bit(file);
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

void bs_put_bit(BS_File_Ptr file, int value) {
    unsigned char val = !!value;
    if (val) {
        BIT_SET(file->buffer, 7 - file->bit_offset);
    } else {
        BIT_CLEAR(file->buffer, 7 - file->bit_offset);
    }
    file->bit_offset++;
    if (file->bit_offset > 7) {
        fputc(file->buffer, file->fp);
        file->buffer = 0;
        file->bit_offset = 0;
    }
}

void bs_put_bits(BS_File_Ptr file, unsigned int bits, unsigned int count) {
    int i;
    for (i = 0; i < count; i++) {
        bs_put_bit(file, BIT_GET(bits, count - i - 1));
    }
}

void bs_close_stream(BS_File_Ptr file) {
    while (file->bit_offset != 0) {
        bs_put_bit(file, 0);
    }
}