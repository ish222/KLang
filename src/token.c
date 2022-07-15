#include "../include/token.h"

Token* token_create(int type, char* value, int line, char* error) {
    Token* token = (Token*)xmalloc(sizeof(Token));
    token->type = (char*)xmalloc_str(sizeof(char)*16);
    strcpy(token->type, TokenName[type]);  // Copies the string of the type provided using the TokenName string array
    token->value = (char*)xmalloc_str(10*sizeof(char));
    strcpy(token->value, value);
    token->line = line;
    token->num_type = type;
    token->error = (char*)xmalloc_str(32*sizeof(char));
    strcpy(token->error, error);
    return token;
}

TokenList* token_list_create(TokenList* tokenList, int size) {
    tokenList->size = size;
    tokenList->tokens = xmalloc(sizeof(Token)*size);
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
