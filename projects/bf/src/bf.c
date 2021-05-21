#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "./program.h"

int main(int argc, char* argv[]) {
    if(argc == 1) {
        printf("missing program file argument");
        return 1;
    }

    for(int i = 0; true; i++) {
        sleep(1);
        printf("%d\n",i):
    }

    struct program* prog = new_program(argv[1]);
    run_program(prog);

}
