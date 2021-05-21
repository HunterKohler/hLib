#ifndef PROJECTS_BF_PROGRAM_H_
#define PROJECTS_BF_PROGRAM_H_

#include <unistd.h>

#include "./io.h"


#define MEMSIZE 1000

struct loop_node {
    char* pos;
    struct loop_node* outer;
};

struct loop_node* new_loop_node(char* pos, struct loop_node* outer) {
    struct loop_node* node = malloc(sizeof *node);
    node->pos = pos;
    node->outer = outer;
    return node;
}

struct program {
    FILE* file;
    fpos_t size;
    char* body;
    char* head;
    char* end;
    char* memory;
    char* address;
    struct loop_node* loop_head;
};

struct program* new_program(char* filename) {
    struct program* prog = malloc(sizeof *prog);
    prog->file = fopen(filename, "r");
    prog->size = fsize(prog->file);
    prog->body = malloc(prog->size * sizeof *prog->body);
    fread(prog->body, sizeof *prog->body, prog->size, prog->file);
    prog->memory = calloc(MEMSIZE, sizeof *prog->memory);
    prog->head = prog->body;
    prog->address = prog->memory;
    prog->end = prog->body + prog->size + 1; // past-end
    return prog;
}

void free_program(struct program* prog) {
    fclose(prog->file);
    free(prog->body);
    free(prog->memory);
    free(prog);
}

// void reset_program(struct program* prog) {

// }

void step_program(struct program* prog) {
    switch(*prog->head) {
        case '>':
            ++prog->address;
            break;

        case '<':
            --prog->address;
            break;

        case '+':
            ++*prog->address;
            break;

        case '-':
            --*prog->address;
            break;

        case '.':
            printf("%c",*prog->address);
            break;

        case ',':
            scanf("%c",prog->address);
            break;

        case '[':
            if(prog->address == 0) {
                while(*prog->head != ']') {
                    ++prog->head;
                    if(prog->head == prog->end) {
                        printf("unmatched opening brace");
                        exit(1);
                    }
                }
            } else {
                prog->loop_head = new_loop_node(prog->head, prog->loop_head);
            }
            break;

        case ']':
            if(prog->loop_head) {
                if(prog->address) {
                    prog->head = prog->loop_head->pos;
                } else {
                    prog->loop_head = prog->loop_head->outer;
                }
            } else {
                printf("unexpected closing brace");
                exit(1);
            }
            break;
    }

    ++prog->head;
}

void run_program(struct program* prog) {
    while(prog->head != prog->end) {
        step_program(prog);
    }
}

void print_program(struct program* prog) {
    printf("program: \n"
           "    size: %lld\n"
           "    body: %s\n"
           "    head: %ld\n"
           "    address: %ld\n"
           "    memory: ",
                prog->size,
                prog->body,
                prog->head - prog->body,
                prog->address - prog->memory
           );

    char* max_address = prog->memory;
    char* memory_end = prog->memory + MEMSIZE;
    for(char* pos = prog->memory; pos != memory_end; ++pos) {
        if(*pos) {
            max_address = pos;
        }
    }

    for(char* pos = prog->memory; pos != max_address; ++pos) {
        printf("%d ",*pos);
    }
    printf("\n");
}


#endif