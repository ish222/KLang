#include "../include/util.h"

void* xmalloc(const size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        printf("Could not allocate memory.\n");
        exit(1);
    }
    return ptr;
}

void* xmalloc_str(const size_t size) {
    void* ptr = xmalloc(size);
    memset(ptr, 0, size);
    return ptr;
}

char* read_input() {
    char* buffer = (char*)xmalloc_str(32);  // Arbitrary sized buffer to hold the input
    fgets(buffer, 32, stdin);  // Reads into the buffer from the console using stdin
    buffer[strcspn(buffer, "\n")] = 0;  // Replaces trailing newline in input with null terminator
    return buffer;
}
