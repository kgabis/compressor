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
#define CPS_FILE_EXTENSION "cps"

enum {
    CPSMaxLeafVal = 300,
    CPSEndOfBlock = 256
};

enum CompressorResult {
    CPSRSuccess = 1,
    CPSRFail = 0
};

enum CompressorResult compressor_compress(const char *source_filename,
                                          const char *destination_filename);
enum CompressorResult compressor_decompress(const char *source_filename,
                                            const char *destination_filename);

#endif
