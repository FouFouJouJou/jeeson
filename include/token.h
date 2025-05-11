#ifndef __TOKEN_H__
#define __TOKEN_H__
#include <stdio.h>
#include <stdint.h>

typedef uint16_t tokens_size_t;

enum token_type_t {
  RIGHT_CURLY
  ,LEFT_CURLY
  ,RIGHT_BRACKET
  ,LEFT_BRACKET
  ,BOOLEAN
  ,NUMBER
  ,QUOTES
  ,COMMA
  ,COLON
  ,SPACE
  ,STRING_LITERAL
  ,DOT
  ,EXP_LOW
  ,EXP_UP
  ,PLUS
  ,MINUS
  ,NULL_
  ,NOT_SUPPORTED
};

struct token_t {
  /* TODO: store token line and character position in file */
  struct position {
    uint8_t x, y;
  } pos;
  enum token_type_t type;
  char *literal;
  size_t length;
};

enum token_type_t symbol_to_token_type(char literal);
char *token_type_to_string(enum token_type_t type);
void printf_token(struct token_t token);
void printf_tokens(struct token_t **tokens, size_t size, void (*printf_function)(struct token_t token));
void free_token(struct token_t *token);

#endif
