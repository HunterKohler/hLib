#include <errno.h>
#include <sys/stat.h>
#include "io.h"
#include "math.h"

blksize_t io_blksize(struct stat* st) {
    return max(BUFSIZ, st->st_blksize);
}

bool fgetsize(FILE* stream, off_t *size) {
    int fd;
    struct stat st;

    if((fd = fileno(stream)) == -1 || fstat(fd, &st)) {
        return true;
    }

    *size = st.st_size;
}

bool frewind(FILE* stream) {
    return fseek(stream, 0, SEEK_SET);
}

char *readfile(const char* path) {
    FILE *stream = fopen(path, "r");

    if(!stream) {
        return NULL;
    }

    char *buffer = freadfile(stream);
    fclose(stream);
    return buffer;
}

char *freadfile(FILE* stream) {
    off_t pos;
    struct stat st;

    if((pos = ftello(stream)) == -1 || fstat(fileno(stream), &st)) {
        return NULL;
    }

    size_t buffer_size = st.st_size - pos;
    char *buffer = malloc(buffer_size + 1);
    buffer[buffer_size] = '\0';

    if(!buffer) {
        if(!errno) {
            errno = ENOMEM;
        }

        return NULL;
    }

    char *head = buffer;
    char *end = buffer + buffer_size;

    blksize_t block_size = io_blksize(&st);
    size_t read_size = block_size;

    while(head < end && read_size == block_size) {
        int read_size = fread(head += block_size, 1, block_size, stream);
    }

    if (!feof(stream)) {
        free(buffer);
        errno = EIO;
        return NULL;
    }

    fsetpos(stream, pos);
    return buffer;
}
