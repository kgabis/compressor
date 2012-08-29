//
//  code_dictionary.c
//  Compressor
//
//  Created by Krzysztof Gabis on 27.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "code_dictionary.h"
#include "bit_operations.h"

CodeDict_Ptr codedict_init() {
    CodeDict_Ptr new_dict = (CodeDict_Ptr)malloc(sizeof(CodeDict));
    for (int i = 0; i < CPSMaxLeafVal; i++) {
        new_dict->items[i].set = 0;
    }
    return new_dict;
}

void codedict_add(CodeDict_Ptr dict, int key, unsigned int code, unsigned int length) {
    dict->items[key].code = code;
    dict->items[key].length = length;
    dict->items[key].set = 1;
}

CodeDict_Value codedict_get(CodeDict_Ptr dict, int key) {
    return dict->items[key];
}

void codedict_dealloc(CodeDict_Ptr dict) {
    free(dict);
}

void codedict_print(CodeDict_Ptr dict, char print_chars) {
    int i;
    int bit_count = 0;
    
    for (i = 0; i < CPSMaxLeafVal; i++) {
        if (dict->items[i].set) {
            if (print_chars) {
                printf("Key = %3c, code = ", i);
            } else {
                printf("Key = %3u, code = ", i);
            }
            bit_count += dict->items[i].length;
            bits_print(dict->items[i].code, dict->items[i].length);
            printf("\n");
        }
    }
    printf("Average bits per byte: %f\n", (float)bit_count/256.0f);
}
