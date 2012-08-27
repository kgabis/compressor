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


BS_File_Ptr bs_open_file(const char *filename) {
    BS_File_Ptr new_file = (BS_File_Ptr)malloc(sizeof(BS_File));
    return new_file;
}

int bs_get_bits(BS_File_Ptr file, unsigned int count) {
    return 0;
}

void bs_put_bits(BS_File_Ptr file, unsigned int bits, unsigned int count) {
    
}

void bs_close_file(BS_File_Ptr file) {
    
}