//
//  count_dictionary.h
//  Compressor
//
//  Created by Krzysztof Gabis on 24.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#ifndef Compressor_count_dictionary_h
#define Compressor_count_dictionary_h

struct count_dict_kvpair_t {
    unsigned char key;
    unsigned long value;
};

typedef struct count_dict_kvpair_t CountDict_KVPair;
typedef CountDict_KVPair * CountDict_KVPair_Ptr;

struct cdictionary_t {
    CountDict_KVPair *items;
    unsigned int count;
    unsigned int capacity;
};

typedef struct cdictionary_t CountDict;
typedef CountDict * CountDict_Ptr;

CountDict_Ptr countdict_init();
void countdict_add(CountDict_Ptr dict, unsigned char key, unsigned long value);
void countdict_increment_count(CountDict_Ptr dict, unsigned char key);
//returns value or 0, if there is no key
unsigned long countdict_get(CountDict_Ptr dict, unsigned char key);
void countdict_dealloc(CountDict_Ptr dict);
//fills output with null-terminated array of keys
void countdict_get_keys(CountDict_Ptr dict, unsigned char * output);
void countdict_print(CountDict_Ptr dict);

#endif
