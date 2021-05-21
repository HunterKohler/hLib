#ifndef PROJECTS_BF_IO_H_
#define PROJECTS_BF_IO_H_

#include <stdio.h>

fpos_t fsize(FILE* file) {
    fpos_t initial;
    fpos_t end;

    fgetpos(file, &initial);

    while(!feof(file)) {
        fgetc(file);
    }

    fgetpos(file, &end);
    fsetpos(file, &initial);

    return end;
}


#endif