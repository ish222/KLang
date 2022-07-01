#ifndef KLANG_TOKEN_H
#define KLANG_TOKEN_H

#include <stdio.h>
#include <crtdefs.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// This is to easily track the type of the token
typedef enum {
    T_VOID = 0,
    T_INT,
    T_FLOAT,
    T_PLUS,
    T_MINUS,
    T_MUL,
    T_DIV,
    T_LBRAC,
    T_RBRAC,
    T_EOF
} TokenType;

// Strings of type names with elements analogous to TokenType enum
static char* TokenName[] = {
        "T_VOID",
        "T_INT",
        "T_FLOAT",
        "T_PLUS",
        "T_MINUS",
        "T_MUL",
        "T_DIV",
        "T_LBRAC",
        "T_RBRAC",
        "T_EOF"
};

// Struct to hold the data for each token
typedef struct {
    char* type;
    char* value;
    int line;
    char* error;
} Token;

// Struct to hold all the tokens together
typedef struct {
    int size;
    int index;
    Token** tokens;
} TokenList;

Token* token_create(int type, char* value, int line, char* error);  // Creates and initialises a token on the heap with the provided member data

TokenList* token_list_create(TokenList* tokenList, int size);  // Creates and initialises a tokenList object to hold tokens
void token_list_add_token(TokenList* tokenList, Token* token);  // Adds a given token to a given tokenList
void token_list_destroy(TokenList* tokenList);  // Deallocates heap allocated memory of all tokens and its member variables

#endif //KLANG_TOKEN_H
