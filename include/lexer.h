#ifndef __LEXER_H__
#define __LEXER_H__
#include <token.h>
tokens_size_t lex(char *buffer, size_t buff_size, struct token_t ***tokens);
#endif
