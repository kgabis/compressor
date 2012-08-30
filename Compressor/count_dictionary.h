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
    unsigned char is_set;
    int key;
    unsigned long value;
};

typedef struct count_dict_kvpair_t CountDict_KVPair;

struct countdict_t {
    CountDict_KVPair items[300];
    unsigned int count;
    unsigned int capacity;
};

typedef struct countdict_t CountDict;
typedef CountDict * CountDict_Ptr;

CountDict_Ptr countdict_init();
void countdict_add(CountDict_Ptr dict, int key, unsigned long value);
void countdict_increment_count(CountDict_Ptr dict, int key);
unsigned long countdict_get(CountDict_Ptr dict, int key);
int * countdict_get_keys(CountDict_Ptr dict);
void countdict_save_to_file(CountDict_Ptr dict, FILE *fp);
CountDict_Ptr countdict_load_from_file(FILE *fp);
void countdict_dealloc(CountDict_Ptr dict);
void countdict_print(CountDict_Ptr dict);

#endif
