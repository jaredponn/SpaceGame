#include "Util.h"
#include <stdio.h>
#include <string.h>

void* safe_malloc(const size_t n) {
        void* p = malloc(n);
        if (p == NULL) {
                fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", n);
                abort();
        }
        return p;
}

char* UTI_strcat(const char* str0, const char* str1) {
        char* newstr = malloc(sizeof(char) * (strlen(str0) + strlen(str1) + 1));
        strcat(newstr, str0);
        strcat(newstr, str1);
        return newstr;
}
