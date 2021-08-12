#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <hlibc/io.h>

#include "bf.h"

int main(int argc, char *argv[]) {
    if(argc == 2 && !strcmp(argv[1], "help")) {
        printf(usage);
        exit(0);
    }

    const char short_options[] = "hqvV";
    const struct option long_options[] = {
        { "version", no_argument, NULL, 'V' },
        { "help", no_argument, NULL, 'h' }
    };

    int opt;
    int index_ptr;
    while((opt = getopt_long(argc, argv, short_options, long_options, &index_ptr)) != -1) {
        switch(opt) {
        case 0:
            break;
        case 'h':
            printf("%s\n", usage);
            exit(0);
        case 'V':
            printf("%s\n", version);
            exit(0);
        case '?':
            if(isprint(optopt)) {
                fprintf(stderr, "Unknown option '-%c'\n%s\n", optopt, usage);
            } else {
                fprintf(stderr, "Unknown non-printable option '-\\x%x\n%s\n", optopt, usage);
            }
            exit(1);
        }
    }

    if(optind == argc) {
        fprintf(stderr, "No input files\n");
        exit(1);
    }

    FILE* fp = fopen(argv[optind], "r");

    if(!fp) {
        perror("Error opening file");
        exit(1);
    }

    size_t length = fsize(fp);

    if(length == -1) {
        perror("Error reading file");
        exit(1);
    }

    // 10 MB
    if(length > 1e7) {
        perror("File too large");
    }

    char* buffer = malloc(length + 1);

    if(!buffer) {
        perror("Error allocating memory");
        fclose(fp);
        exit(1);
    }

    if(fread(buffer, 1, length, fp) != length) {
        perror("Error reading file");
        fclose(fp);
        free(buffer);
        exit(1);
    }

    buffer[length] = '\0';

    struct bf_result* result = bf_compile(buffer, length);

    if(result->err) {
        fprintf(stderr, "Compiler error: %s @%zu\n", BF_STRERROR[result->err], result->err_pos);
        exit(1);
    }

    FILE* cfile = fopen("temp.c", "w");
    fprintf(cfile, BF_TEMPLATE, result->buffer);
    fclose(cfile);

    // system("gcc temp.c -lncurses");
}


struct bf_result* bf_compile(char* source, int length) {
    struct bf_result* ret = malloc(sizeof *ret);

    if(!ret) {
        return NULL;
    }

    ret->err = 0;
    ret->buffer = malloc((sizeof *ret));

    if(!ret->buffer) {
        free(ret->buffer);
        ret->err = BF_ERR_MEM;
        return ret;
    }

    int braces = 0;
    char* head = ret->buffer;

    for(int i = 0; i < length; ++i) {
        switch(source[i]) {
        case '>': *head = 'r'; break;
        case '<': *head = 'l'; break;
        case '+': *head = 'i'; break;
        case '-': *head = 'd'; break;
        case '.': *head = 'p'; break;
        case ',': *head = 'g'; break;
        case '[':
            *head = 'w';
            ++braces;
            break;
        case ']':
            if(--braces < 0) {
                free(ret->buffer);
                ret->err = BF_ERR_CLOSE_BRACE;
                ret->err_pos = i;
                return ret;
            }

            *head = '}';
            break;
        default:
            continue;
        }

        *(++head) = ';';
        ++head;
    }

    if(braces) {
        free(ret->buffer);
        ret->err = BF_ERR_EOF;
        ret->err_pos = length;
        return ret;
    }

    return ret;
}
