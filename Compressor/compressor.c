//
//  compressor.c
//  Compressor
//
//  Created by Krzysztof Gabis on 24.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include "compressor.h"

CDictionary_Ptr count_byte_occurences(const char *filename) {
    CDictionary_Ptr cdict = cdict_init();
    FILE *fp = fopen(filename, "rb");
    int c;
    if (fp == NULL){
        puts("Error: Wrong filename.");
        return NULL;
    }
    c = EOF;
    while((c = fgetc(fp)) != EOF) {
        cdict_increment_count(cdict, (unsigned char)c);
    }    
    fclose(fp);
    return cdict;
}