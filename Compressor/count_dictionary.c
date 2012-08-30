//
//  count_dictionary.c
//  Compressor
//
//  Created by Krzysztof Gabis on 24.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "count_dictionary.h"

#include "compressor.h"

enum {
    CDStartingSize = CPSMaxLeafVal
};

CountDict_Ptr countdict_init() {
    CountDict_Ptr new_dict = (CountDict_Ptr)malloc(sizeof(CountDict_Ptr));
    new_dict->items = (CountDict_KVPair*)malloc(CDStartingSize * sizeof(CountDict_KVPair));
    for (int i = 0; i < CDStartingSize; i++) {
        new_dict->items[i].is_set = 0;
        new_dict->items[i].key = i;
        new_dict->items[i].value = 0;
    }
    new_dict->_capacity = CDStartingSize;
    new_dict->count = 0;
    return new_dict;
}

void countdict_add(CountDict_Ptr dict, int key, unsigned long value) {
    int truncated_key = key % dict->_capacity;
    if (dict->items[truncated_key].is_set == 0) {
        dict->count++;
    }
    dict->items[truncated_key].is_set = 1;
    dict->items[truncated_key].value = value;
}

void countdict_increment_count(CountDict_Ptr dict, int key) {
    int truncated_key = key % dict->_capacity;
    if (dict->items[truncated_key].is_set == 0) {
        dict->count++;
    }
    dict->items[truncated_key].is_set = 1;
    dict->items[truncated_key].value++;
}

int * countdict_get_keys(CountDict_Ptr dict) {
    int i;
    int result_index = 0;
    int * result = (int*)malloc(sizeof(int) * dict->count);
    for (i = 0 ; i < dict->_capacity; i++) {
        if (dict->items[i].is_set) {
            result[result_index] = dict->items[i].key;
            result_index++;
        }
    }
    return result;
}

unsigned long countdict_get(CountDict_Ptr dict, int key) {
    int truncated_key = key % dict->_capacity;
    if (dict->items[truncated_key].is_set) {
        return dict->items[truncated_key].value;
    } else {
        return 0;
    }
}

void countdict_print(CountDict_Ptr dict) {
    int i;
    int *keys = countdict_get_keys(dict);
    for (i = 0; i < dict->count; i++) {
        printf("Key = %u, count = %lu\n", keys[i], countdict_get(dict, keys[i]));
    }
    free(keys);
}

void countdict_dealloc(CountDict_Ptr dict) {
    free(dict->items);
    free(dict);
}