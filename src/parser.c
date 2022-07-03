#include "../include/parser.h"

NumberNode* cast_to_number_node(void* node) { return (NumberNode*)node; }
BinaryOpNode* cast_to_binary_node(void* node) { return (BinaryOpNode*)node; }
UnaryOpNode* cast_to_unary_node(void* node) { return (UnaryOpNode*)node; }

NumberNode* create_number_node(Token* token, char* value) {
    NumberNode* node = (NumberNode*)xmalloc(sizeof(NumberNode));
    node->token = token;
    node->type = NUMBERNODE;
    node->value = (char*)xmalloc(sizeof(char)*16);
    memset(node->value, 0, 16);
    strcpy(node->value, value+2);
    return node;
}

BinaryOpNode* create_binary_node(void* left_node, int left_type, Token* op_token, void* right_node, int right_type, char* value) {
    BinaryOpNode* node = (BinaryOpNode*)xmalloc(sizeof(BinaryOpNode));
    node->op_token = op_token;
    node->type = BINARYOPNODE;
    node->value = (char*)xmalloc(sizeof(char)*64);
    memset(node->value, 0, 64);
    node->value[0] = '(';
//    strcat(node->value, value);
    switch (left_type) {
        case NUMBERNODE: {
            strcat(node->value, ((NumberNode*)left_node)->value);
            node->left_node = (NumberNode*)left_node;
            node->left_node = cast_to_number_node(node->left_node);
            break;
        }
        case BINARYOPNODE:
            strcat(node->value, ((BinaryOpNode*)left_node)->value);
            node->left_node = (BinaryOpNode*)left_node;
            node->left_node = cast_to_binary_node(node->left_node);
            break;
        case UNARYOPNODE:
            strcat(node->value, ((UnaryOpNode*)left_node)->value);
            node->left_node = (UnaryOpNode*)left_node;
            node->left_node = cast_to_unary_node(node->left_node);
            break;
        default:
            printf("Invalid left node type supplied\n");
            free(node->value);
            free(node);
            return NULL;
    }
    strcat(node->value, ", ");
    strcat(node->value, op_token->type+2);
    strcat(node->value, ", ");
    switch (right_type) {
        case NUMBERNODE:
            strcat(node->value, ((NumberNode*)right_node)->value);
            node->right_node = (NumberNode*)right_node;
            node->right_node = cast_to_number_node(node->right_node);
            break;
        case BINARYOPNODE:
            strcat(node->value, ((BinaryOpNode*)right_node)->value);
            node->right_node = (BinaryOpNode*)right_node;
            node->right_node = cast_to_binary_node(node->right_node);
            break;
        case UNARYOPNODE:
            strcat(node->value, ((UnaryOpNode*)right_node)->value);
            node->right_node = (UnaryOpNode*)right_node;
            node->right_node = cast_to_unary_node(node->right_node);
            break;
        default:
            printf("Invalid right node type supplied\n");
            free(node->value);
            free(node);
            return NULL;
    }
    strcat(node->value, ")");
    return node;
}

UnaryOpNode* create_unary_node(Token* op_token, void* right_node, int right_type, char* value) {
    UnaryOpNode* node = (UnaryOpNode*)xmalloc(sizeof(UnaryOpNode));
    node->op_token = op_token;
    node->type = UNARYOPNODE;
    node->value = (char*)xmalloc(sizeof(char)*64);
    memset(node->value, 0, 64);
    strcpy(node->value, value);
    switch (right_type) {
        case NUMBERNODE:
            right_node = cast_to_number_node(right_node);
            node->node = cast_to_number_node(node->node);
            memcpy(node->node, right_node, sizeof(NumberNode));
            break;
        case BINARYOPNODE:
            right_node = cast_to_binary_node(right_node);
            node->node = cast_to_binary_node(node->node);
            memcpy(node->node, (BinaryOpNode*)right_node, sizeof(BinaryOpNode));
            break;
        case UNARYOPNODE:
            right_node = cast_to_unary_node(right_node);
            node->node = cast_to_unary_node(node->node);
            memcpy(node->node, right_node, sizeof(UnaryOpNode));
            break;
        default:
            printf("Invalid node type supplied\n");
            free(node->value);
            free(node);
            return NULL;
    }
    return node;
}

ParseResultList* create_parse_result_list(ParseResultList* list, int size) {
    list->size = size;
    list->results = xmalloc(sizeof(ParseResult)*size);
    list->index = 0;
    return list;
}

ParseResult* create_parse_result(void* result_node, int node_type, char* error) {
    ParseResult* result = (ParseResult*)xmalloc(sizeof(ParseResult));
    result->error = (char*)xmalloc(sizeof(char)*32);
    memset(result->error, 0, 32);
    strcpy(result->error, error);
    if (result_node == NULL) return result;
    switch (node_type) {
        case NUMBERNODE:
            result->node = (NumberNode*)result_node;
            result->node = cast_to_number_node(result->node);
            result->value = ((NumberNode*)result_node)->value;
            break;
        case BINARYOPNODE:
            result->node = (BinaryOpNode*)result_node;
            result->node = cast_to_binary_node(result->node);
            result->value = ((BinaryOpNode*)result_node)->value;
            break;
        case UNARYOPNODE:
            result->node = (UnaryOpNode*)result_node;
            result->node = cast_to_unary_node(result->node);
            result->value = ((UnaryOpNode*)result_node)->value;
            break;
        default:
            printf("Invalid right node type supplied\n");
            free(result->error);
            free(result);
            return NULL;
    }
    return result;
}

void add_parse_result(ParseResultList* list, ParseResult* result) {
    assert(list->index < list->size);
    list->results[list->index++] = result;
}

ParseResultList* parse(TokenList* tokenList) {
    ParseResultList* resultList = (ParseResultList*)xmalloc(sizeof(ParseResultList));
    resultList = create_parse_result_list(resultList, tokenList->index);
    int index = 0;
    Token* cur_tok = advance(tokenList, &index);
    while(index < tokenList->index) {
        switch (cur_tok->num_type) {
            case T_INT:
            case T_FLOAT: {
                ParseResult* res = get_factor(tokenList, cur_tok, &index);
                add_parse_result(resultList, res);
                break;
            }
            case T_PLUS:
            case T_MINUS: {
                ParseResult* res;
            }
            default: {
                ParseResult* res = create_parse_result(NULL, VOID, "InvalidSyntaxError");
                add_parse_result(resultList, res);
            }
        }
    }
    return resultList;
}

Token* advance(TokenList* tokenList, int* index) {
    if (*index < tokenList->index)
        return tokenList->tokens[(*index)++];
    else return NULL;
}

ParseResult* get_factor(TokenList* list, Token* cur_tok, int* index) {
    Token* last_tok = cur_tok;
    cur_tok = advance(list, index);
    if (cur_tok->num_type == T_PLUS || cur_tok->num_type == T_MINUS || cur_tok->num_type == T_MUL || cur_tok->num_type == T_DIV) {
        ParseResult* result = get_binary_op(list, last_tok, cur_tok, index);
        return result;
    }
    else if (cur_tok == NULL) {
        char temp[64];
        strcpy(temp, last_tok->type);
        strcat(temp, ":");
        strcat(temp, last_tok->value);
        NumberNode* node = create_number_node(last_tok, temp);
        ParseResult* result = create_parse_result(node, NUMBERNODE, "\0");
        return result;
    }
    else return NULL;
}

ParseResult* get_binary_op(TokenList* list, Token* last_tok, Token* cur_tok, int* index) {
    Token* op_tok = cur_tok;
    cur_tok = advance(list, index);
    if (cur_tok->num_type == T_INT || cur_tok->num_type == T_FLOAT) {
        char temp[64] = {0};
        strcpy(temp, last_tok->type);
        strcat(temp, ":");
        strcat(temp, last_tok->value);
        NumberNode* last_node = create_number_node(last_tok, temp);
        memset(temp, 0, strlen(temp));
        strcpy(temp, cur_tok->type);
        strcat(temp, ":");
        strcat(temp, cur_tok->value);
        NumberNode* next_node = create_number_node(cur_tok, temp);
        BinaryOpNode* node = create_binary_node(last_node, last_tok->num_type, op_tok, next_node, cur_tok->num_type, temp);
        ParseResult* result = create_parse_result(node, BINARYOPNODE, "\0");
        return result;
    }
    else return NULL;
}

void print_parse_results(ParseResultList* list) {
    for(int i = 0; i < list->index; ++i) {
        if (strncmp(list->results[i]->error, "\0", 1) == 0) {
            //if (strncmp(list->results[i]->value, "\0", 1) != 0)
                printf("%s\n", list->results[i]->value);
            //else printf("%s\n", list->results[i]->value);
        }
        else {
            printf("\nError: %s '%s'\n", list->results[i]->error, list->results[i]->value);
            break;
        }
    }
}

void number_node_destroy(NumberNode* node) { free(node->value); }
void binary_node_destroy(BinaryOpNode* node) { free(node->value); }
void unary_node_destroy(UnaryOpNode* node) { free(node->value); }

void parse_list_destroy(ParseResultList* list) {
    for(int i = 0; i < list->index; ++i) {

    }
}

