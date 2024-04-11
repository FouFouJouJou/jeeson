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
  ,NOT_SUPPORTED
};

struct token_t {
  enum token_type_t type;
  char *literal;
  size_t length;
};

enum token_type_t symbol_to_token_type(char literal);
void printf_token(struct token_t token);
void free_token(struct token_t *token);

#endif
