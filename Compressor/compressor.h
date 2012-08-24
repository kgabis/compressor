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

CDictionary_Ptr count_byte_occurences(const char *filename);

#endif
