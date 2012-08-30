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

//TODO: Encoding data in blocks
enum CompressionType {
    CPSTHuffman = 0
};

struct compressed_block_t {
    enum CompressionType compression_type;
    size_t size;
    char *data;
};

typedef struct compressed_block_t Compressed_Block;

static void print_file_bitpattern(const char *filename, size_t offset) {
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

void compressor_test() {
    char source_filename[] = "/users/kgabis/code/objc/mine/Compressor/test_long.txt";
    char *compressed_filename;
    char decompressed_filename[] = "/users/kgabis/code/objc/mine/Compressor/test_d.txt";
    compressed_filename = (char*)calloc(strlen(source_filename) + strlen(CPS_FILE_EXTENSION) + 2, 1);
    sprintf(compressed_filename, "%s.%s", source_filename, CPS_FILE_EXTENSION);
    enum CompressorResult result;
    result = compressor_compress(source_filename, compressed_filename);
    if (result == CPSRSuccess) {
        printf("Compression success!\n");
    } else {
        printf("Compression fail :(");
        return;
    }
    result = compressor_decompress(compressed_filename, decompressed_filename);
    if (result == CPSRSuccess) {
        printf("Decompression success!\n");
    } else {
        printf("Decompression fail :(");
        return;
    }
    //print_file_bitpattern(compressed_filename, sizeof(CountDict));
}



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
    if (source_fp == NULL) {
        return CPSRFail;
    }
    destination_fp = fopen(destination_filename, "wb");
    if (destination_fp == NULL) {
        return CPSRFail;
    }
    destination_stream = bs_open_stream(destination_fp, BSTWrite);
    countdict = countdict_count_in_file(source_fp);
    tree = tree_grow_from_countdict(countdict);
    codedict = tree_get_codedict(tree);
    fclose(source_fp);
    source_fp = fopen(source_filename, "rb");
    countdict_save_to_file(countdict, destination_fp);
    while ((c = fgetc(source_fp)) != EOF) {
        codedict_value = codedict_get(codedict, c);
        bs_put_bits(destination_stream, codedict_value.code, codedict_value.length);
    }
    codedict_value = codedict_get(codedict, CPSEndOfBlock);
    bs_put_bits(destination_stream, codedict_value.code, codedict_value.length);
    
    bs_close_stream(destination_stream);
    fclose(source_fp);
    fclose(destination_fp);
    
    tree_dealloc(tree);
    countdict_dealloc(countdict);
    codedict_dealloc(codedict);
    return CPSRSuccess;
}

enum CompressorResult compressor_decompress(const char *source_filename,
                                            const char *destination_filename) {
    FILE *source_fp;
    FILE *destination_fp;
    Bit_Stream_Ptr source_stream;
    CountDict_Ptr countdict;
    Tree_Ptr tree;
    int c;
    source_fp = fopen(source_filename, "rb");
    if (source_fp == NULL) {
        return CPSRFail;
    }
    destination_fp = fopen(destination_filename, "wb");
    if (destination_fp == NULL) {
        return CPSRFail;
    }
    countdict = countdict_load_from_file(source_fp);
    if (countdict == NULL) {
        return CPSRFail;
    }
    source_stream = bs_open_stream(source_fp, BSTRead);
    tree = tree_grow_from_countdict(countdict);
    while ((c = tree_walk(tree, source_stream)) != CPSEndOfBlock) {
        fputc(c, destination_fp);
    }
    
    bs_close_stream(source_stream);
    fclose(source_fp);
    fclose(destination_fp);
    
    tree_dealloc(tree);
    countdict_dealloc(countdict);           
    return CPSRSuccess;
}