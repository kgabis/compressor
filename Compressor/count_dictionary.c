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

enum {
    CDStartingSize = 256
};

CountDict_Ptr countdict_init() {
    CountDict_Ptr new_dict = (CountDict_Ptr)malloc(sizeof(CountDict_Ptr));
    new_dict->items = (CountDict_KVPair*)malloc(CDStartingSize * sizeof(CountDict_KVPair));
    new_dict->capacity = CDStartingSize;
    new_dict->count = 0;
    return new_dict;
}

void countdict_add(CountDict_Ptr dict, unsigned char key, unsigned long value) {
    int i;
    for (i = 0; i < dict->count; i++) {
        if (dict->items[i].key == key) {
            dict->items[i].value = value;
            return;
        }
    }
    if (dict->count == dict->capacity) {
        dict->capacity = dict->capacity * 2;
        dict->items = realloc(dict->items, dict->capacity);
    }
    dict->items[dict->count].key = key;
    dict->items[dict->count].value = value;
    dict->count++;
}

void countdict_increment_count(CountDict_Ptr dict, unsigned char key) {
    int i;
    for (i = 0; i < dict->count; i++) {
        if (dict->items[i].key == key) {
            dict->items[i].value++;
            return;
        }
    }
    if (dict->count == dict->capacity) {
        //TODO: realloc
        return;
    }
    dict->items[dict->count].key = key;
    dict->items[dict->count].value = 1;
    dict->count++;
}

//returns value or 0, if there is no key
unsigned long countdict_get(CountDict_Ptr dict, unsigned char key) {
    int i;
    for (i = 0; i < dict->count; i++) {
        if (dict->items[i].key == key) {
            return dict->items[i].value;
        }
    }
    return 0;
}

void countdict_print(CountDict_Ptr dict) {
    int i;
    for (i = 0; i < dict->count; i++) {
        printf("Key = %u, count = %lu\n", dict->items[i].key, dict->items[i].value);
    }
}

void countdict_get_keys(CountDict_Ptr dict, unsigned char * output) {
    //TODO: implementation
}

void countdict_dealloc(CountDict_Ptr dict) {
    free(dict->items);
    free(dict);
}