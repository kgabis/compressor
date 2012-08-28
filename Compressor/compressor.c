//
//  compressor.c
//  Compressor
//
//  Created by Krzysztof Gabis on 24.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include "compressor.h"

CountDict_Ptr count_byte_occurences(const char *filename) {
    CountDict_Ptr cdict = countdict_init();
    FILE *fp = fopen(filename, "rb");
    int c;
    if (fp == NULL){
        puts("Error: Wrong filename.");
        return NULL;
    }
    c = EOF;
    while((c = fgetc(fp)) != EOF) {
        countdict_increment_count(cdict, (unsigned char)c);
    }
    countdict_increment_count(cdict, CPSEndOfBlock);
    fclose(fp);
    return cdict;
}