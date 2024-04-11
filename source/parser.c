#include <string.h>
#include <lexer.h>
#include <json.h>
#include <parser.h>

#define YANK(tokens) *tokens++


struct json_value_t *parse_value(struct token_t ***tokens, size_t size) {
  struct token_t *token=YANK((*tokens));
  switch(token->type) {
    case BOOLEAN:
      return create_json_value((void*)create_json_bool(!strncmp(token->literal, "true", 4) ? true : false), J_BOOL);
    case STRING_LITERAL:
      return create_json_value((void*)create_json_string(token->literal, token->length), J_STRING);
    case NUMBER:
      return create_json_value((void*)create_json_int(atoi(token->literal)), J_INT);
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

