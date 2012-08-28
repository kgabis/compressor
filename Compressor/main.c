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
#include "bit_stream.h"
//#define BIT_SET(byte, ix, val) (byte = (byte & ~(!val << ix)) | (val << ix))
//#define BIT_GET(byte, ix) ((byte >> ix) & 1u)


//What next?
//TODO: Saving compressed file (bitstream? bitqueue?)
//TODO: Decompressing file

int main(int argc, const char * argv[])
{
//    bits_print(0xf0, 0xff);
//    printf("\n");
//    printf("%d\n", bits_count_ones(0xf0));
    bs_test();
//    CountDict_Ptr countdict = count_byte_occurences("/users/kgabis/code/objc/mine/Compressor/test.pdf");
//    Tree_Ptr tree = tree_grow_from_countdict(countdict);
//    CodeDict_Ptr codedict = tree_get_codedict(tree);
//    codedict_print(codedict, 0);
//    tree_dealloc(tree);
//    countdict_dealloc(countdict);

    printf("Done!\n");
    return 0;
}



