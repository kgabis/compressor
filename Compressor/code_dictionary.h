//
//  code_dictionary.h
//  Compressor
//
//  Created by Krzysztof Gabis on 27.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#ifndef Compressor_code_dictionary_h
#define Compressor_code_dictionary_h

#include "compressor.h"

struct codedict_value_t {
    unsigned char set;
    unsigned int code;
    unsigned int length;
};

typedef struct codedict_value_t CodeDict_Value;

struct codedict_t {
    CodeDict_Value items[CPSMaxLeafVal];
};

typedef struct codedict_t CodeDict;
typedef CodeDict * CodeDict_Ptr;

CodeDict_Ptr codedict_init();
void codedict_add(CodeDict_Ptr dict, int key, unsigned int code, unsigned int length);
CodeDict_Value codedict_get(CodeDict_Ptr dict, int key);
void codedict_dealloc(CodeDict_Ptr dict);
void codedict_print(CodeDict_Ptr dict, char print_chars);

#endif
