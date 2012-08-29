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
#include <time.h>
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
    compressor_test();
//    bs_test();
    printf("Done!\n");
    return 0;
}



