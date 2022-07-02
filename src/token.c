#include "../include/token.h"

Token* token_create(int type, char* value, int line, char* error) {
    Token* token = (Token*)malloc(sizeof(Token));
    assert(token != NULL);
    token->type = (char*)malloc(sizeof(char)*16);
    assert(token->type != NULL);
    memset(token->type, 0, 16);
    strcpy(token->type, TokenName[type]);  // Copies the string of the type provided using the TokenName string array
    token->value = (char*)malloc(10*sizeof(char));
    assert(token->value != NULL);
    memset(token->value, 0, 10);
    strcpy(token->value, value);
    token->line = line;
    token->num_type = type;
    token->error = (char*)malloc(32*sizeof(char));
    assert(token->error != NULL);
    memset(token->error, 0, 32);
    strcpy(token->error, error);
    return token;
}

TokenList* token_list_create(TokenList* tokenList, int size) {
    tokenList->size = size;
    tokenList->tokens = malloc(sizeof(Token)*size);
    tokenList->index = 0;
    return tokenList;
}

void token_list_add_token(TokenList* tokenList, Token* token) {
    assert(tokenList->index < tokenList->size);
    tokenList->tokens[tokenList->index++] = token;  // Assigns the token to the index then increments index
}

void token_list_destroy(TokenList* tokenList) {
    for(int i = 0; i < tokenList->index; ++i) {  // Iterates through all tokens in the list to free its member variable memory
        free(tokenList->tokens[i]->type);
        free(tokenList->tokens[i]->value);
        free(tokenList->tokens[i]->error);
        free(tokenList->tokens[i]);
    }
    free(tokenList->tokens);
}
