//
//  main.c
//  Compressor
//
//  Created by Krzysztof Gabis on 22.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "bit_operations.h"
#include "priority_queue.h"
#include "count_dictionary.h"
#include "compressor.h"
//#define BIT_SET(byte, ix, val) (byte = (byte & ~(!val << ix)) | (val << ix))
//#define BIT_GET(byte, ix) ((byte >> ix) & 1u)


//What next?
//TODO: Converting node dictionary to balanced tree
//TODO: Saving compressed file (bitstream? bitqueue?)
//TODO: Decompressing file

int main(int argc, const char * argv[])
{
    CDictionary_Ptr dict = count_byte_occurences("/users/kgabis/code/objc/mine/Compressor/test.pdf");
    cdict_print(dict);
    cdict_dealloc(dict);
    
    // insert code here...
    printf("Done!\n");
    return 0;
}



