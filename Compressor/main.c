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
    ETWrongOption
};

static void print_help() {
    printf("Usage:\n");
    printf("Compressing:   compressor -c INPUT_FILE [-o OUTPUT_FILE]\n");
    printf("Decompressing: compressor -d INPUT_FILE [-o OUTPUT_FILE]\n");
}

static char * remove_extension(char *string_with_extension) {
    char *string_without_extension;
    char *last_dot;
    if (string_with_extension == NULL) {
        return NULL;
    }
    string_without_extension = (char*)malloc(strlen(string_with_extension) + 1);
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
    Compressor_Operation operation;
    enum CompressorResult operation_result;
    const char *input_filename = NULL;
    const char *output_filename = NULL;
    char operation_string[256];
    int arguments_ok = 0;
    enum ErrorType error_type = ETNoError;
    
    while ((argc > 1) && (argv[0][0] == '-'))
	{
		switch (argv[0][1])
		{
			case 'c':
                strcpy(operation_string, "Compressing");
                printf("Compress: %s\n", argv[1]);
                operation = compressor_compress;
                input_filename = argv[1];
                argv++;
                argc--;
                if (arguments_ok || argc == 1) {
                    error_type = ETWrongNumberOfArguments;
                    goto error;
                } else {
                    arguments_ok = 1;
                }
				break;
			case 'd':
                strcpy(operation_string, "Decompressing");
				printf("Decompress: %s\n", argv[1]);
                operation = compressor_decompress;
                input_filename = argv[1];
                argv++;
                argc--;
                if (arguments_ok || argc == 1) {
                    error_type = ETWrongNumberOfArguments;
                    goto error;
                } else {
                    arguments_ok = 1;
                }
				break;                
            case 'o':
                printf("Output: %s\n", argv[1]);
                output_filename = argv[1];
                argv++;
                argc--;
				break;
			default:
                error_type = ETWrongOption;
		}
		argv++;
		argc--;
	}
    
    if (arguments_ok) {
        operation_result = operation(input_filename, output_filename);
    } else {
        error_type = ETWrongNumberOfArguments;
        goto error;
    }
    
    switch (operation_result) {
        case CPSRSuccess:
            printf("%s %s successfull.\n", operation_string, input_filename);
            break;
        case CPSRFail:
            printf("%s %s failed.\n", operation_string, input_filename);
            error_type = ETOperationFailed;
            goto error;
            break;
        default:
            break;
    }    
    return 0;
error:
    switch (error_type) {
        case ETWrongNumberOfArguments:
            printf("Error: Wrong number of arguments.\n");
            break;
        case ETWrongOption:
            printf("Wrong option: %s\n", argv[1]);
            break;
        case ETOperationFailed:
            break;
        default:
            break;
    }
    print_help();
    return 1;
}