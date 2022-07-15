#include "../include/lexer.h"

TokenList* create_tokens(char* text) {
    TokenList* tokenList = (TokenList*)xmalloc(sizeof(TokenList));
    tokenList = token_list_create(tokenList, (int)strlen(text));
    int index = -1;
    char current_char = lexer_advance(&index, text);  // Advances to the first character in the text
    int line_num = 1;

    while (current_char != '\0') {
        switch (current_char) {
            case ' ':
            case '\t':
                current_char = lexer_advance(&index, text);  // Whitespace is ignored
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                char* str_num = (char*)xmalloc_str(10*sizeof(char));  // Used to keep track of the number until the token is finalised
                int dot_count = 0;  // Tracks the number of decimal places
                const char* search_string = "0123456789.";  // Acceptable numeric characters searched for in the while loop condition below
                while (current_char != '\0' && strchr(search_string, current_char) != NULL) {
                    if (current_char == '.') {
                        if (dot_count == 1) {  // More than one decimal place raises error
                            Token* token = token_create(T_VOID, ".", line_num, "IllegalCharError");
                            token_list_add_token(tokenList, token);
                            return tokenList;
                        }
                        ++dot_count;
                        strcat(str_num, ".");  // Concatenates decimal point to number string
                    }
                    else strncat(str_num, &current_char, 1);
                    current_char = lexer_advance(&index, text);
                }
                if (dot_count == 0) {  // No decimal places = integer
                    Token* token = token_create(T_INT, str_num, line_num, "\0");
                    token_list_add_token(tokenList, token);
                    free(str_num);
                    break;
                }
                else {
                    Token* token = token_create(T_FLOAT, str_num, line_num, "\0");
                    token_list_add_token(tokenList, token);
                    free(str_num);
                    break;
                }
            }
            case '+': {
                Token* token = token_create(T_PLUS, "\0", line_num, "\0");
                token_list_add_token(tokenList, token);
                current_char = lexer_advance(&index, text);
                break;
            }
            case '-': {
                Token* token = token_create(T_MINUS, "\0", line_num, "\0");
                token_list_add_token(tokenList, token);
                current_char = lexer_advance(&index, text);
                break;
            }
            case '*': {
                Token* token = token_create(T_MUL, "\0", line_num, "\0");
                token_list_add_token(tokenList, token);
                current_char = lexer_advance(&index, text);
                break;
            }
            case '/': {
                Token* token = token_create(T_DIV, "\0", line_num, "\0");
                token_list_add_token(tokenList, token);
                current_char = lexer_advance(&index, text);
                break;
            }
            case '(': {
                Token* token = token_create(T_LBRAC, "\0", line_num, "\0");
                token_list_add_token(tokenList, token);
                current_char = lexer_advance(&index, text);
                break;
            }
            case ')': {
                Token* token = token_create(T_RBRAC, "\0", line_num, "\0");
                token_list_add_token(tokenList, token);
                current_char = lexer_advance(&index, text);
                break;
            }
            default: {  // No acceptable characters were found so IllegalCharError is raised
                Token* token = token_create(T_VOID, &current_char, line_num, "IllegalCharError");
                token_list_add_token(tokenList, token);
                return tokenList;
            }
        }
    }
    return tokenList;
}

char lexer_advance(int* index, const char* text) {
    // Increments the index value provided and returns the char at that index of the text
    return text[++(*index)];
}

void print_tokens(TokenList* tokenList) {
    printf("Lexer output:\n");
    for(int i = 0; i < tokenList->index; ++i) {
        if (tokenList->tokens[i] != NULL && strncmp(tokenList->tokens[i]->error, "\0", 1) == 0) {
            if (strncmp(tokenList->tokens[i]->value, "\0", 1) != 0)
                printf("(%s : %s)\n", tokenList->tokens[i]->type, tokenList->tokens[i]->value);
            else printf("(%s)\n", tokenList->tokens[i]->type);
        }
        else if (tokenList->tokens[i] != NULL){
            printf("\n%s '%c' at line %d\n", tokenList->tokens[i]->error, tokenList->tokens[i]->value[0], tokenList->tokens[i]->line);
            break;
        }
        else printf("Unknown error when lexing.\n");
    }
    printf("End of lexer output.\n\n");
}
