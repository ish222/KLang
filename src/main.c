#include <stdio.h>
#include <string.h>

#include "../include/util.h"
#include "../include/lexer.h"

int main(int argc, char** argv) {
    printf("<stdin> ");
    char* input = read_input();  // Reads input until newline
    TokenList* tokenList = create_tokens(input);  // Lexes through the input to create tokens
    print_tokens(tokenList);  // Prints each generated token and its value
    free(input);
    token_list_destroy(tokenList);  // Deallocates the heap allocated members of the tokenList struct
    free(tokenList);
    return 0;
}
