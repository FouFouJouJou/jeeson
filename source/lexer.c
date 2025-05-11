#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <token.h>
#include <lexer.h>
#include <stdint.h>

struct token_t *literal_to_token(char *literal, size_t literal_size, enum token_type_t type) {
  struct token_t *token=malloc(sizeof(struct token_t));
  token->type=type;
  token->literal=malloc((literal_size+1)*sizeof(char));
  token->literal=strncpy(token->literal, literal, literal_size);
  token->length=literal_size;
  token->literal[literal_size]='\0';
  if (type == STRING_LITERAL) {
    token->length=literal_size+2;
  }
  return token;
}

struct token_t *lex_string(char *input) {
  struct token_t *token=0;
  char *start=input, *delims="\"\0";
  if (*start != '"') goto out;
  size_t letters=strcspn(start+1, delims);
  if (start[1+letters] != '\"') {
    fprintf(stderr, "[ERROR] string literal missing closing quotes");
    exit(67);
  }
  token=literal_to_token(start+1, letters, STRING_LITERAL);
  out:
    return token;
}

struct token_t *lex_digits(char *input) {
  struct token_t *token=0;
  char *digits="0123456789", *start=input;
  size_t total=strspn(start, digits);
  if (total==0) {
    goto out;
  }
  token=literal_to_token(input, total, NUMBER);
  out:
    return token;
}

struct token_t *lex_symbol(char input) {
  struct token_t *token=0;
  char *symbols=":,[]{}+-.Ee", *symbol;
  if ((symbol=strchr(symbols, input)) == 0) {
    goto out;
  }
  enum token_type_t type=symbol_to_token_type(*symbol);
  token=literal_to_token(symbol, 1, type);
  out:
    return token;
}

struct token_t *lex_boolean(char *start) {
  struct token_t *token=0;
  char *false_string="false", *true_string="true";
  char *boolean_string=0;
  if (!strncmp(start, "false", 5)) {
    boolean_string=false_string;
  }
  if (!strncmp(start, "true", 4)) {
    boolean_string=true_string;
  }
  if (!boolean_string) {
    goto out;
  }
  token=literal_to_token(boolean_string, strlen(boolean_string), BOOLEAN);
  out:
    return token;
}

struct token_t *lex_null(char *start) {
  struct token_t *token=0;
  if (!strncmp(start, "null", 4)) token=literal_to_token(start, 4, NULL_);
  out:
    return token;
}
tokens_size_t lex(char *buffer, size_t buff_size, struct token_t ***tokens_p) {
  char *start=buffer, *delims=" \n\r\t";
  tokens_size_t total=0;
  while (start < buffer+buff_size-1) {
    struct token_t *token=0;
    start+=strspn(start, delims);
    if (token=lex_null(start));
    else if (token=lex_symbol(*start));
    else if (token=lex_boolean(start));
    else if (token=lex_string(start));
    //else if (token=lex_zero(start));
    else if (token=lex_digits(start));
    if (!token) exit(160);
    *tokens_p=realloc(*tokens_p, (++total)*sizeof(struct token_t*));
    *(*tokens_p+total-1)=token;
    start+=token->length;
  }
  return total;
}
