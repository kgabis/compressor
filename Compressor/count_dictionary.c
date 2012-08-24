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

CDictionary_Ptr cdict_init() {
    CDictionary_Ptr new_dict = (CDictionary_Ptr)malloc(sizeof(CDictionary_Ptr));
    new_dict->values = (CDKVPair*)malloc(CDStartingSize * sizeof(CDKVPair));
    new_dict->capacity = CDStartingSize;
    new_dict->used = 0;
    return new_dict;
}

void cdict_add(CDictionary_Ptr dict, unsigned char key, unsigned long value) {
    int i;
    for (i = 0; i < dict->used; i++) {
        if (dict->values[i].key == key) {
            dict->values[i].value = value;
            return;
        }
    }
    if (dict->used == dict->capacity) {
        //TODO: realloc
        return;
    }
    dict->values[dict->used].key = key;
    dict->values[dict->used].value = value;
    dict->used++;
}

void cdict_increment_count(CDictionary_Ptr dict, unsigned char key) {
    int i;
    for (i = 0; i < dict->used; i++) {
        if (dict->values[i].key == key) {
            dict->values[i].value++;
            return;
        }
    }
    if (dict->used == dict->capacity) {
        //TODO: realloc
        return;
    }
    dict->values[dict->used].key = key;
    dict->values[dict->used].value = 1;
    dict->used++;
}

//returns value or 0, if there is no key
unsigned long cdict_get(CDictionary_Ptr dict, unsigned char key) {
    int i;
    for (i = 0; i < dict->used; i++) {
        if (dict->values[i].key == key) {
            return dict->values[i].value;
        }
    }
    return 0;
}

void cdict_print(CDictionary_Ptr dict) {
    int i;
    for (i = 0; i < dict->used; i++) {
        printf("Key = %u, count = %lu\n", dict->values[i].key, dict->values[i].value);
    }
}

void cdict_getkeys(CDictionary_Ptr dict, unsigned char * output) {
    //TODO: implementation
}

void cdict_dealloc(CDictionary_Ptr dict) {
    free(dict->values);
    free(dict);
}