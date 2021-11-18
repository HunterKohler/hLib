#include <stddef.h>

extern const char hex_charset[];
size_t hex_len(size_t n);
char *hex_encode(char *restrict dest, const char *restrict src, size_t n);
char *hex_decode(char *restrict dest, const char *restrict src, size_t n);

extern const char base64_charset[];
size_t base64_len(size_t n);
char *base64_encode(char *restrict dest, const char *restrict src, size_t n);
char *base64_decode(char *restrict dest, const char *restrict src, size_t n);
