#ifndef BF_H_
#define BF_H_

const char version[] = "0.0.1";
const char usage[] = "Usage: bf [options] file";

struct bf_result {
    int err;
    union {
        char* buffer;
        size_t err_pos;
    };
};

static const char BF_TEMPLATE[] =
"#include<stdio.h>\n"
"#include<stdint.h>\n"
"int8_t z[30000];\n"
"int8_t *x = z;\n"
"#define r ++x\n"
"#define l --x\n"
"#define i ++*x\n"
"#define d --*x\n"
"#define p putchar(*x)\n"
"#define g *x=getchar()\n"
"#define w while(*x){\n"
"int main() { %s }";

enum bf_error {
    BF_ERR_EOF,
    BF_ERR_MEM,
    BF_ERR_CLOSE_BRACE
};

static const char* BF_STRERROR[] = {
    [BF_ERR_EOF] = "Unexpected EOF",
    [BF_ERR_MEM] = "Could not allocate memory",
    [BF_ERR_CLOSE_BRACE] = "Unexpected closing brace",
};

struct bf_result* bf_compile(char* source, int length);


#endif
