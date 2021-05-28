#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "debug.h"
#include "generics.h"

int fprint_usage(FILE *stream, char *name) {
    return fprintf(stream, "Usage: %s [options] file\n", name ? name : "bf");
}

bool in_charset(char c) {
    return c == '>'
        || c == '<'
        || c == '+'
        || c == '-'
        || c == '.'
        || c == ','
        || c == '['
        || c == ']';
}

void xalloc_error() {
    fprintf(stderr, "Error allocating memory.\n");
    exit(1);
}

void* xmalloc(size_t size) {
    void* mem = malloc(size);

    if(!mem) {
        xalloc_error();
    }

    return mem;
}

void* xcalloc(size_t count, size_t size) {
    void* mem = calloc(count, size);

    if(!mem) {
        xalloc_error();
    }

    return mem;
}

void* xrealloc(void* ptr, size_t size) {
    ptr = realloc(ptr, size);

    if(!ptr) {
        xalloc_error();
    }

    return ptr;
}

int main(int argc, char* argv[]) {
    if(argc > 2) {
        fprintf(stderr, "Error: Too many arguments\n");
        fprint_usage(stderr, argv[0]);
        exit(errno);
    } else if(argc < 2) {
        fprintf(stderr, "Error: Missing file argument\n");
        fprint_usage(stderr, argv[0]);
        exit(errno);
    }

    FILE* stream = fopen(argv[1], "r");

    if(errno) {
        perror("Error opening file");
        exit(errno);
    }

    fseek(stream, 0, SEEK_END);
    int64_t stream_length = ftello(stream);
    fseek(stream, 0, SEEK_SET);

    if(errno) {
        perror("Error reading file");
        exit(errno);
    }

    char *body = xmalloc(stream_length * sizeof(*body));
    char *body_ptr = body;
    for(int64_t s_index = 0; s_index < stream_length; ++s_index) {
        char tmp = fgetc(stream);
        if(in_charset(tmp)) {
            *(body_ptr++) = tmp;
        }
    }

    int64_t body_length = body_ptr - body;
    body = xrealloc(body, body_length  * sizeof(*body));
    body_ptr = body;
    char *body_end = body + body_length;

    int memory_size = 1000;
    char *memory = xcalloc(memory_size, sizeof(*memory));
    char *memory_ptr = memory;
    char *memory_end = memory + memory_size;

    int lstack_size = 1000;
    char **lstack = xcalloc(lstack_size, sizeof(*lstack));
    char **lstack_ptr = lstack;
    char **lstack_end = lstack + lstack_size;

    while(body_ptr < body_end) {

        switch(*body_ptr) {
            case '>':
                ++memory_ptr;
                break;

            case '<':
                --memory_ptr;
                break;

            case '+':
                ++(*memory_ptr);
                break;

            case '-':
                --(*memory_ptr);
                break;

            case '.':
                printf("%c", *memory_ptr);
                break;

            case ',':
                scanf("%c", memory_ptr);
                break;

            case '[':
                // TODO save last ']' if seen possible
                if(*memory_ptr) {
                    if(lstack_ptr == lstack_end) {
                        fprintf(stderr, "Loop overflow\n");
                        exit(1);
                    }

                    *(++lstack_ptr) = body_ptr;
                } else {
                    while(*body_ptr != ']') {
                        if(body_ptr == body_end) {
                            fprintf(stderr, "Unexceptected EOF while parsing\n");
                            exit(1);
                        }

                        ++body_ptr;
                    }
                }
                break;

            case ']':
                if(lstack_ptr == lstack) {
                    fprintf(stderr, "Unmatched closing brace\n");
                    exit(1);
                }

                if(*memory_ptr) {
                    body_ptr = *lstack_ptr;
                } else {
                    --lstack_ptr;
                }
                break;
        }

        ++body_ptr;
    }

    // printf("\n");
    // for(char *ptr = memory; ptr - memory < 10; ++ptr) {
    //     printf("%d, ", *ptr);
    // }

    // printf("\n");
}
