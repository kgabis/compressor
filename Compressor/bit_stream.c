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
    BS_File_Ptr bs_file = bs_open_stream(fp);
    bs_put_bits(bs_file, 0x4, 4);
    bs_put_bits(bs_file, 0x1, 4);
    fclose(fp);
    fp = fopen(filename, "rb");
    int c;
    while((c = fgetc(fp)) != EOF) {
        bits_print(c, 0xff);
        printf("\n");
        printf("%c\n", c);
    }
    fclose(fp);
}

BS_File_Ptr bs_open_stream(FILE *file) {
    BS_File_Ptr new_bsfile = (BS_File_Ptr)malloc(sizeof(BS_File));
    new_bsfile->fp = file;
    new_bsfile->buffer_index = 0;
    new_bsfile->byte_buffer = 0;
    return new_bsfile;
}

int bs_get_bits(BS_File_Ptr file, unsigned int count) {
    int result = 0;
    int i;
    for (i = 0; i < count; i++) {
        if (file->buffer_index == 8) {
            file->byte_buffer = fgetc(file->fp);
            file->buffer_index = 0;
        }
        result = (result << 1) | BIT_GET(file->byte_buffer, file->buffer_index);
        file->buffer_index++;
    }
    return result;
}

static void put_bit(BS_File_Ptr file, int value) {
    unsigned char val = !!value;    
    if (val) {
        BIT_SET(file->byte_buffer, 7 - file->buffer_index);
    } else {
        BIT_CLEAR(file->byte_buffer, 7 - file->buffer_index);
    }
    file->buffer_index++;
    if (file->buffer_index > 7) {
        putc(file->byte_buffer, file->fp);
        file->byte_buffer = 0;
        file->buffer_index = 0;
    }
}

void bs_put_bits(BS_File_Ptr file, unsigned int bits, unsigned int count) {
    int i;
    for (i = 0; i < count; i++) {
        put_bit(file, BIT_GET(bits, count - i - 1));
    }
}

void bs_close_stream(BS_File_Ptr file) {
    
}