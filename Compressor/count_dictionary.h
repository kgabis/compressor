//
//  count_dictionary.h
//  Compressor
//
//  Created by Krzysztof Gabis on 24.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#ifndef Compressor_count_dictionary_h
#define Compressor_count_dictionary_h

typedef struct cdkvpair_t {
    unsigned char key;
    unsigned long value;
} CDKVPair;

typedef CDKVPair * CDKVPair_Ptr;

typedef struct cdictionary_t {
    CDKVPair *values;
    unsigned int used;
    unsigned int capacity;
} CDictionary;

typedef CDictionary * CDictionary_Ptr;

CDictionary_Ptr cdict_init();
void cdict_add(CDictionary_Ptr dict, unsigned char key, unsigned long value);
void cdict_increment_count(CDictionary_Ptr dict, unsigned char key);
//returns value or 0, if there is no key
unsigned long cdict_get(CDictionary_Ptr dict, unsigned char key);
void cdict_dealloc(CDictionary_Ptr dict);
//fills output with null-terminated array of keys
void cdict_getkeys(CDictionary_Ptr dict, unsigned char * output);
void cdict_print(CDictionary_Ptr dict);

#endif
