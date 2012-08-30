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

struct person_t {
    char first_name[256];
    char last_name[256];
};

int main(int argc, const char * argv[])
{
    compressor_test();
//    bs_test();
//    struct person_t person = { "Krzysztof", "Gabis"};
//    struct person_t person_read;
//    FILE *fp = fopen("/users/kgabis/code/objc/mine/Compressor/test_person.txt", "wb");
//    fwrite(&person, 1, sizeof(struct person_t), fp);
//    fclose(fp);
//    fp = fopen("/users/kgabis/code/objc/mine/Compressor/test_person.txt", "rb");
//    fread(&person_read, 1, sizeof(struct person_t), fp);
//    printf("%s %s", person_read.first_name, person_read.last_name);
//    fclose(fp);
    printf("\nDone!\n");
    return 0;
}



