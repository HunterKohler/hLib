#ifndef HLIB_UTILS_C_FSIZE_H_
#define HLIB_UTILS_C_FSIZE_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

fpos_t fsize(FILE* file) {
    fpos_t initial;
    fpos_t end;

    while(!feof(file)) {
        fgetc(file);
    }

    fgetpos(file, &end);
    fsetpos(file, &initial);

    return end;
}

#ifdef __cplusplus
}
#endif

#endif