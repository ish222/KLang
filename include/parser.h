#ifndef KLANG_PARSER_H
#define KLANG_PARSER_H

#include "token.h"
#include "util.h"

#define NODE_VALUE_SIZE 64

typedef enum {
    VOID = 0,
    NUMBERNODE,
    BINARYOPNODE,
    UNARYOPNODE
} NodeType;

typedef struct {
    int type;
    Token* token;
    char* value;
} NumberNode;

typedef struct {
    int type;
    void* left_node;
    Token* op_token;
    void* right_node;
    char* value;
} BinaryOpNode;

typedef struct {
    int type;
    Token* op_token;
    void* node;
    char* value;
} UnaryOpNode;

NumberNode* cast_to_number_node(void* node);
BinaryOpNode* cast_to_binary_node(void* node);
UnaryOpNode* cast_to_unary_node(void* node);

NumberNode* create_number_node(Token* token, char* value);
BinaryOpNode* create_binary_node(void* left_node, int left_type, Token* op_token, void* right_node, int right_type, char* value);
UnaryOpNode* create_unary_node(Token* token, void* right_node, int right_type, char* value);

typedef struct {
    char* error;
    void* node;
    char* value;
} ParseResult;

typedef struct {
    int size;
    int index;
    ParseResult** results;
} ParseResultList;

ParseResultList* create_parse_result_list(ParseResultList* list, int size);
ParseResult* create_parse_result(void* result_node, int node_type, char* error);
void add_parse_result(ParseResultList* list, ParseResult* result);

ParseResultList* parse(TokenList* tokens);
Token* advance(TokenList* tokens, int* index);
ParseResult* get_factor(TokenList* list, Token* cur_tok, int* index);
ParseResult* get_binary_op(TokenList* list,Token* last_tok, Token* cur_tok, int* index);
ParseResult* get_term(TokenList* list);
ParseResult* get_expression(TokenList* tokens);

void print_parse_results(ParseResultList* list);

void number_node_destroy(NumberNode* node);
void binary_node_destroy(BinaryOpNode* node);
void unary_node_destroy(UnaryOpNode* node);
void parse_list_destroy(ParseResultList* list);

#endif //KLANG_PARSER_H
