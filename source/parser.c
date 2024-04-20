#include <string.h>
#include <assert.h>
#include <lexer.h>
#include <json.h>
#include <parser.h>

#define YANK(tokens) *(tokens)++
#define ASSERT_T(tokens, type_check) assert((*tokens)->type == type_check);


struct json_number_t *parse_number(struct token_t ***tokens) {
  struct json_number_t *result=calloc(1, sizeof(struct json_number_t));
  size_t length=0;
  char *digits=0, *fraction=0, *exp=0,
       minus='-', plus='+', e='E', dot='.', sign=plus;
  ASSERT_T(*tokens, NUMBER)
  struct token_t *token=YANK(*tokens);
  if(*(token->literal) == '0' && token->length != 1) exit(199);
  result->type=J_DIGITS;
  digits=token->literal;
  length+=token->length;
  result->value=realloc(result->value, sizeof(char)*(length+1));
  if((**tokens)->type == DOT) {
    YANK(*tokens);
    result->type=J_FRACTION;
    length+=1;
    ASSERT_T(*tokens, NUMBER);
    token=YANK(*tokens);
    length+=token->length;
    fraction=token->literal;
  }

  if((**tokens)->type == EXP_LOW || (**tokens)->type == EXP_UP) {
    YANK(*tokens);
    length+=1;
    assert((**tokens)->type == MINUS || (**tokens)->type == PLUS || (**tokens)->type == NUMBER);
    token=YANK(*tokens);
    if(token->type == MINUS) {
      sign=minus;
      ASSERT_T(*tokens, NUMBER);
      token=YANK(*tokens);
      length+=token->length;
    }
    else if(token->type == PLUS) {
      sign=plus;
      ASSERT_T(*tokens, NUMBER);
      token=YANK(*tokens);
      length+=token->length;
    }
    if(token->type == NUMBER) {
      exp=token->literal;
      length+=token->length;
      YANK(*tokens);
    }
    result->type=J_EXP;
  }
  printf("%s.%se%c%s(%d)\n", digits, fraction, sign, exp, length);
  return result;
}

struct json_number_t *parse_signed_number(struct token_t ***tokens) {
  YANK(*tokens);
  struct json_number_t *result=parse_number(tokens);
  result->sign=1;
  return result;
}

struct json_value_t *parse_value(struct token_t ***tokens, size_t size) {
  struct token_t *token=YANK((*tokens));
  switch(token->type) {
    case BOOLEAN:
      return create_json_value((void*)create_json_bool(!strncmp(token->literal, "true", 4) ? true : false), J_BOOL);
    case STRING_LITERAL:
      return create_json_value((void*)create_json_string(token->literal, token->length), J_STRING);
    case NUMBER:
      (*tokens)--;
      struct json_number_t *number=parse_number(tokens);
      return create_json_value((void*)number, J_NUMBER);
      break;
    case MINUS:
      (*tokens)--;
      struct json_number_t *signed_number=parse_signed_number(tokens);
      return create_json_value((void*)signed_number, J_NUMBER);
      break;
    case LEFT_CURLY:
      return create_json_value((void*)parse_object(tokens, size), J_OBJECT);
    case LEFT_BRACKET:
      return create_json_value((void*)parse_array(tokens, size), J_ARRAY);
    default:
      exit(78);
  }
  return 0;
}

struct json_object_t *parse(char *buff, size_t size) {
  struct token_t **tokens=0;
  tokens_size_t read_tokens=lex(buff, size, &tokens);
  if((YANK(tokens))->type != LEFT_CURLY) exit(68);
  struct json_object_t *object=parse_object(&tokens, read_tokens);
  tokens-=read_tokens;
  for(int i=0; i<read_tokens; ++i) free_token(*(tokens+i));
  free(tokens);
  return object;
}


struct json_array_t *parse_array(struct token_t ***tokens, size_t size) {
  struct json_array_t *array=calloc(1, sizeof(struct json_array_t));
  array->size=0;
  while((**tokens)->type != RIGHT_BRACKET) {
    if((**tokens)->type == COMMA) YANK((*tokens));
    struct json_value_t *json_value=parse_value(tokens, size);
    array->size+=1;
    array->elements=realloc(array->elements, array->size*sizeof(struct json_value_t *));
    array->elements[array->size-1]=json_value;
  }
  YANK((*tokens));
  return array;
}

struct json_object_t *parse_object(struct token_t ***tokens, size_t size) {
  struct json_object_t *object=calloc(1, sizeof(struct json_object_t));
  object->size=0;
  while((**tokens)->type != RIGHT_CURLY) {
    if((**tokens)->type == COMMA) YANK((*tokens));
    struct token_t *key=YANK((*tokens));
    struct token_t *colon=YANK((*tokens));
    struct json_string_t *json_key=create_json_string(key->literal, key->length);
    struct json_value_t *json_value=parse_value(tokens, size);
    object->size+=1;
    object->keys=realloc(object->keys, object->size*sizeof(struct json_string_t*));
    object->values=realloc(object->values, object->size*sizeof(struct json_value_t*));
    object->keys[object->size-1]=json_key;
    object->values[object->size-1]=json_value;
  }
  YANK((*tokens));
  return object;
}

