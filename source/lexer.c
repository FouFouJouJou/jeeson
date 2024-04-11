#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <token.h>
#include <lexer.h>
#include <stdint.h>

struct token_t *literal_to_token(char *literal, size_t literal_size, enum token_type_t type) {
  struct token_t *token=malloc(sizeof(struct token_t));
  token->type=type;
  switch(type) {
    case STRING_LITERAL:
      token->length=literal_size+2;
      token->literal=malloc((literal_size+1)*sizeof(char));
      token->literal=strncpy(token->literal, literal, literal_size);
      token->literal[literal_size]='\0';
      break;
    case NUMBER:
      token->literal=malloc((literal_size+1)*sizeof(char));
      token->literal=strncpy(token->literal, literal, literal_size);
      token->literal[literal_size]='\0';
      token->length=strlen(token->literal);
      break;
    default:
      token->literal=malloc((literal_size+1)*sizeof(char));
      *(token->literal)=*literal;
      token->type=type;
      token->length=literal_size;
      token->literal[literal_size]='\0';
  }
  return token;
}

struct token_t *lex_string(char *input) {
  struct token_t *token=0;
  char *start=input, *delims="\"";
  if(*start != '"') goto out;
  size_t letters=strcspn(start+1, delims);
  token=literal_to_token(start+1, letters, STRING_LITERAL);
  out:
    return token;
}

struct token_t *lex_number(char *input) {
  struct token_t *token=0;
  char *digits="0123456789", *start=input;
  size_t total=strspn(start, digits);
  if(total==0) goto out;
  token=literal_to_token(input, total, NUMBER);
  out:
    return token;
}

struct token_t *lex_symbol(char input) {
  struct token_t *token=0;
  char *symbols=":,[]{}", *symbol;
  if((symbol=strchr(symbols, input)) == 0) goto out;
  enum token_type_t type=symbol_to_token_type(*symbol);
  token=literal_to_token(symbol, 1, type);
  out:
    return token;
}
tokens_size_t lex(char *buffer, size_t buff_size, struct token_t ***tokens_p) {
  char *start=buffer, *delims=" \n\r\t";
  tokens_size_t total=0;
  while(start < buffer+buff_size-1) {
    struct token_t *token=0;
    start+=strspn(start, delims);
    if((token=lex_symbol(*start)));
    else if((token=lex_string(start)));
    else if((token=lex_number(start)));
    if(!token) exit(160);
    *tokens_p=realloc(*tokens_p, (++total)*sizeof(struct token_t*));
    *(*tokens_p+total-1)=token;
    start+=token->length;
  }
  return total;
}
