//
//  compressor.h
//  Compressor
//
//  Created by Krzysztof Gabis on 24.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#ifndef Compressor_compressor_h
#define Compressor_compressor_h

#include "count_dictionary.h"

enum {
    CPSMaxLeafVal = 300,
    CPSEndOfBlock = 256
};

enum CompressorResult {
    CPSRSuccess = 1,
    CPSRFail = 0
};

void compressor_test();
enum CompressorResult compressor_compress(const char *filename);
CountDict_Ptr count_byte_occurences_in_file(FILE *fp);

#endif
