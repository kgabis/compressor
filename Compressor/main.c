//
//  main.c
//  Compressor
//
//  Created by Krzysztof Gabis on 22.08.2012.
//  Copyright (c) 2012 Krzysztof Gabis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compressor.h"

enum ErrorType {
    ETNoError = 0,
    ETWrongNumberOfArguments = 1,
    ETOperationFailed = 2,
    ETIdenticalFilenames = 3,
    ETWrongOption = 4
};

enum OperationType {
    OTNone = 0,
    OTCompress = 1,
    OTDecompress = 2
};

static void print_help() {
    printf("Usage:\n");
    printf("Compressing:   compressor -c INPUT_FILE [-o OUTPUT_FILE]\n");
    printf("Decompressing: compressor -d INPUT_FILE [-o OUTPUT_FILE]\n");
}

static char * remove_extension(char *string_without_extension, const char *string_with_extension) {
    char *last_dot;
    if (string_with_extension == NULL) {
        return NULL;
    }
    strcpy(string_without_extension, string_with_extension);
    last_dot = strrchr (string_without_extension, '.');
    if (last_dot != NULL) {
        *last_dot = '\0';
    }
    return string_without_extension;
}

int main(int argc, const char * argv[])
{
    if (argc == 1) {
        print_help();
        return 1;
    }
    argv++;
    enum CompressorResult operation_result;
    enum OperationType operation_type = OTNone;
    char *input_filename = (char*)calloc(256, sizeof(char));
    char *output_filename = (char*)calloc(256, sizeof(char));
    enum ErrorType error_type = ETNoError;
    
    while ((argc > 1) && (argv[0][0] == '-'))
	{
		switch (argv[0][1])
		{
			case 'c':
                printf("Compress: %s\n", argv[1]);
                argc--;
                if (operation_type != OTNone || argc == 1) {
                    error_type = ETWrongNumberOfArguments;
                    goto error;
                } else {
                    operation_type = OTCompress;
                }
                strcpy(input_filename, argv[1]);
                argv++;
				break;
			case 'd':
				printf("Decompress: %s\n", argv[1]);
                argc--;
                if (operation_type != OTNone || argc == 1) {
                    error_type = ETWrongNumberOfArguments;
                    goto error;
                } else {
                    operation_type = OTDecompress;
                }
                strcpy(input_filename, argv[1]);
                argv++;
				break;
            case 'o':
                argc--;
                if (argc == 1) {
                    error_type = ETWrongNumberOfArguments;
                    goto error;
                }
                strcpy(output_filename, argv[1]);
                argv++;
                break;
			default:
                error_type = ETWrongOption;
		}
		argv++;
		argc--;
	}
    
    switch (operation_type) {
        case OTCompress:
            if (output_filename[0] == '\0') {
                sprintf(output_filename, "%s.%s", input_filename, CPS_FILE_EXTENSION);
            }
            if (strcmp(input_filename, output_filename) == 0) {
                error_type = ETIdenticalFilenames;
                goto error;
            }
            operation_result = compressor_compress(input_filename, output_filename);
            break;
        case OTDecompress:
            if (output_filename[0] == '\0') {
                remove_extension(output_filename, input_filename);
            }
            if (strcmp(input_filename, output_filename) == 0) {
                error_type = ETIdenticalFilenames;
                goto error;
            }
            operation_result = compressor_decompress(input_filename, output_filename);
            break;
        default:
            break;
    }
    
    switch (operation_result) {
        case CPSRSuccess:
            printf("Operation successful.\n");
            printf("Output: %s\n", output_filename);
            break;
        case CPSRFail:
            printf("Operation failed.\n");
            error_type = ETOperationFailed;
            goto error;
            break;
        default:
            break;
    }
    free(input_filename);
    free(output_filename);
    return 0;
error:
    switch (error_type) {
        case ETWrongNumberOfArguments:
            printf("Error: Wrong number of arguments.\n");
            break;
        case ETWrongOption:
            printf("Wrong option: %s\n", argv[1]);
            break;
        case ETIdenticalFilenames:
            printf("Identical filenames.\n");
            break;
        case ETOperationFailed:
            break;
        default:
            break;
    }
    print_help();
    return 1;
}