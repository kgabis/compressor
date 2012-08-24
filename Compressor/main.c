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
//#define BIT_SET(byte, ix, val) (byte = (byte & ~(!val << ix)) | (val << ix))
//#define BIT_GET(byte, ix) ((byte >> ix) & 1u)




int main(int argc, const char * argv[])
{
    CDictionary_Ptr dict = cdict_init();
    cdict_increment_count(dict, 1);
    cdict_increment_count(dict, 1);
    cdict_increment_count(dict, 2);
    cdict_increment_count(dict, 2);
    cdict_increment_count(dict, 3);
    cdict_increment_count(dict, 3);
    cdict_increment_count(dict, 3);
    cdict_increment_count(dict, 3);
    cdict_increment_count(dict, 1);
    cdict_increment_count(dict, 1);
    cdict_print(dict);
    cdict_dealloc(dict);
//    Tree_Node_Ptr tree = tree_branch_init(NULL);
//    tree_grow(tree, 1, 10);
//    tree_grow(tree, 2, 20);
//    tree_grow(tree, 3, 30);
//    tree_grow(tree, 4, 40);
//    tree_grow(tree, 5, 50);
//    tree_print(tree);
//    tree_dealloc(tree);
    
    // insert code here...
    printf("Done!\n");
    return 0;
}



