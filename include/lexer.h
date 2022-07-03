#ifndef KLANG_LEXER_H
#define KLANG_LEXER_H

#include <stdio.h>

#include "token.h"
#include "util.h"

TokenList* create_tokens(char* text);  // Creates token from input text provided
char lexer_advance(int* index, const char* text);  // Advances to the next character in the text
void print_tokens(TokenList* tokenList);  // Prints the type and value and (if relevant) error of each token in a tokenList

#endif //KLANG_LEXER_H
