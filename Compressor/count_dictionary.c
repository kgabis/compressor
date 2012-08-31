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

CountDict_Ptr countdict_init() {
    CountDict_Ptr new_dict = (CountDict_Ptr)malloc(sizeof(CountDict));
    int i;
    for (i = 0; i < CPSMaxLeafVal; i++) {
        new_dict->items[i].is_set = 0;
        new_dict->items[i].value = 0;
    }
    new_dict->capacity = CPSMaxLeafVal;
    new_dict->count = 0;
    return new_dict;
}

void countdict_add(CountDict_Ptr dict, int key, unsigned long value) {
    int truncated_key = key % dict->capacity;
    if (dict->items[truncated_key].is_set == 0) {
        dict->count++;
    }
    dict->items[truncated_key].is_set = 1;
    dict->items[truncated_key].value = value;
}

void countdict_increment_count(CountDict_Ptr dict, int key) {
    int truncated_key = key % dict->capacity;
    if (dict->items[truncated_key].is_set == 0) {
        dict->count++;
    }
    dict->items[truncated_key].is_set = 1;
    dict->items[truncated_key].value++;
}

int * countdict_get_keys(CountDict_Ptr dict) {
    int i;
    int result_index = 0;
    int *result = (int*)malloc(sizeof(int) * dict->count);
    for (i = 0 ; i < dict->capacity; i++) {
        if (dict->items[i].is_set) {
            result[result_index] = i;
            result_index++;
        }
    }
    return result;
}

unsigned long countdict_get(CountDict_Ptr dict, int key) {
    int truncated_key = key % dict->capacity;
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

static unsigned int get_checksum(CountDict_Ptr dict) {
    int i;
    unsigned int checksum = 0;
    for (i = 0; i < CPSMaxLeafVal; i++) {
        checksum += dict->items[i].value;
    }
    return checksum;
}

void countdict_save_to_file(CountDict_Ptr dict, FILE *fp) {
    dict->checksum = get_checksum(dict);
//    printf("Checksum = %u\n", dict->checksum);
    fwrite(dict, 1, sizeof(CountDict), fp);
}

CountDict_Ptr countdict_load_from_file(FILE *fp) {
    CountDict_Ptr loaded_dict = (CountDict_Ptr)malloc(sizeof(CountDict));
    fseek(fp, 0L, SEEK_END);
    if(ftell(fp) < sizeof(CountDict)) {
        return NULL;
    }
    fseek(fp, 0L, SEEK_SET);
    fread(loaded_dict, 1, sizeof(CountDict), fp);
//    printf("Loaded checksum = %u\n", loaded_dict->checksum);
//    printf("Computed checksum = %u\n", get_checksum(loaded_dict));
    if (loaded_dict->checksum != get_checksum(loaded_dict)) {
        return NULL;
    }
    return loaded_dict;
}

CountDict_Ptr countdict_count_in_file(FILE *fp) {
    CountDict_Ptr cdict = countdict_init();
    int c;
    c = EOF;
    while((c = getc(fp)) != EOF) {
        countdict_increment_count(cdict, (unsigned char)c);
    }
    ungetc(c, fp);
    countdict_increment_count(cdict, CPSEndOfBlock);
    fclose(fp);
    return cdict;
}

void countdict_dealloc(CountDict_Ptr dict) {
    free(dict);
}