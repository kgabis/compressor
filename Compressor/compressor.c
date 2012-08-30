//
//  compressor.c
//  Compressor
//
//  Created by Krzysztof Gabis on 24.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compressor.h"
#include "code_dictionary.h"
#include "tree.h"
#include "count_dictionary.h"
#include "bit_operations.h"

#define CPS_FILE_EXTENSION "cps"

enum CompressionType {
    CPSTHuffman = 0
};

struct compressed_block_t {
    enum CompressionType compression_type;
};

typedef struct compressed_block_t Compressed_Block;

void print_file_bitpattern(const char *filename) {
    FILE *file = fopen(filename, "rb");
    Bit_Stream_Ptr stream = bs_open_stream(file, BSTRead);
    int c;
    int i = 1;
    //printf("%d", fgetc(file));
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
    fclose(file);
}

void compressor_test() {
    char source_filename[] = "/users/kgabis/code/objc/mine/Compressor/test.txt";
    char *destination_filename;
    destination_filename = (char*)calloc(strlen(source_filename) + strlen(CPS_FILE_EXTENSION) + 2, 1);
    sprintf(destination_filename, "%s.%s", source_filename, CPS_FILE_EXTENSION);
    enum CompressorResult result;
    result = compressor_compress(source_filename, destination_filename);
    if (result == CPSRSuccess) {
        printf("Success!\n");
    } else {
        printf("Fail :(");
        return;
    }
    //print_file_bitpattern(destination_filename);
}

static CountDict_Ptr count_byte_occurences_in_file(FILE *fp) {
    CountDict_Ptr cdict = countdict_init();
    int c;
    c = EOF;
    while((c = getc(fp)) != EOF) {
        countdict_increment_count(cdict, (unsigned char)c);
    }
    ungetc(c, fp);
    countdict_increment_count(cdict, CPSEndOfBlock);
    fclose(fp);
    return cdict;
}

//TODO: destination filename as second argument
enum CompressorResult compressor_compress(const char *source_filename,
                                          const char *destination_filename) {
    FILE *source_fp;
    FILE *destination_fp;
    Bit_Stream_Ptr destination_stream;
    CountDict_Ptr countdict;
    CodeDict_Ptr codedict;
    Tree_Ptr tree;
    CodeDict_Value codedict_value;
    int c;
    
    source_fp = fopen(source_filename, "rb");
    destination_fp = fopen(destination_filename, "wb");
    if (source_fp == NULL || destination_fp == NULL) {
        puts("Error: Wrong filename.");
        goto error;
    }
    destination_stream = bs_open_stream(destination_fp, BSTWrite);
    countdict = count_byte_occurences_in_file(source_fp);
    tree = tree_grow_from_countdict(countdict);
    codedict = tree_get_codedict(tree);
    fclose(source_fp);
    source_fp = fopen(source_filename, "rb");
    countdict_save_to_file(countdict, destination_fp);
    printf("POS: %lu\n", ftell(destination_fp));
    while ((c = fgetc(source_fp)) != EOF) {
        codedict_value = codedict_get(codedict, c);
        bs_put_bits(destination_stream, codedict_value.code, codedict_value.length);
    }
    codedict_value = codedict_get(codedict, CPSEndOfBlock);
    bs_put_bits(destination_stream, codedict_value.code, codedict_value.length);
    
    bs_close_stream(destination_stream);
    fclose(source_fp);
    fclose(destination_fp);
    
    countdict_print(countdict);
    codedict_print(codedict, 0);
    
    tree_dealloc(tree);
    countdict_dealloc(countdict);
    codedict_dealloc(codedict);
    return CPSRSuccess;
    
error:
    return CPSRFail;
}

enum CompressorResult compressor_decompress(const char *source_filename,
                                            const char *destination_filename) {
    return CPSRSuccess;
    
error:
    return CPSRFail;
}