#include "../include/util.h"

void* xmalloc(const size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        printf("Could not allocate memory.\n");
        exit(1);
    }
    return ptr;
}

char* read_input() {
    char* buffer = (char*)malloc(32);  // Arbitrary sized buffer to hold the input
    if (!buffer) {
        printf("Could not initialise buffer to read data");
        return NULL;
    }
    memset(buffer, 0, 32);  // Sets the initial value of all characters in the string buffer to null
    fgets(buffer, 32, stdin);  // Reads into the buffer from the console using stdin
    buffer[strcspn(buffer, "\n")] = 0;  // Replaces trailing newline in input with null terminator
    return buffer;
}
