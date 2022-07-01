#include "../include/util.h"

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
