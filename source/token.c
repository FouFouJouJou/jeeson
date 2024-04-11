#include <stdlib.h>
#include <token.h>

char *token_type_to_string(enum token_type_t type) {
  switch(type) {
    case STRING_LITERAL:
      return "STRING_LITERAL";
    case RIGHT_CURLY:
      return "RIGHT_CURLY";
    case LEFT_CURLY:
      return "LEFT_CURLY";
    case RIGHT_BRACKET:
      return "RIGHT_BRACKET";
    case LEFT_BRACKET:
      return "LEFT_BRACKET";
    case NUMBER:
      return "NUMBER";
    case QUOTES:
      return "QUOTES";
    case COMMA:
      return "COMMA";
    case COLON:
      return "COLON";
    case NOT_SUPPORTED:
      return "NOT_SUPPORTED";
    }
}


enum token_type_t symbol_to_token_type(char literal) {
  enum token_type_t result=NOT_SUPPORTED;
  switch(literal) {
    case '{':
      result=LEFT_CURLY;
      break;
    case '}':
      result=RIGHT_CURLY;
      break;
    case ']':
      result=RIGHT_BRACKET;
      break;
    case '[':
      result=LEFT_BRACKET;
      break;
    case '"':
      result=QUOTES;
      break;
    case ':':
      result=COLON;
      break;
    case ',':
      result=COMMA;
      break;
    default:
      result=NOT_SUPPORTED;
      break;
    }
  return result;
}

void printf_token(struct token_t token) {
  printf("(%s, %s)\n", token_type_to_string(token.type), token.literal);
}

void free_token(struct token_t *token) {
  free(token->literal);
  free(token);
}
