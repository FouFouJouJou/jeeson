#ifndef __LEXER_H__
#define __LEXER_H__
#include <token.h>
char *token_type_to_string(enum token_type_t type);
tokens_size_t lex(char *buffer, size_t buff_size, struct token_t ***tokens);
#endif
