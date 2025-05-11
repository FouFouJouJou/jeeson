#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <json.h>

#define INC 2

void insert_spaces(uint8_t level) {
  for (int i=0; i<level; ++i) {
    printf(" ");
  }
}

void printf_object(struct json_object_t object, uint8_t level) {
  printf("{\n");
  for (int i=0; i<object.size; ++i) {
    insert_spaces(level+INC);
    printf("%s: ", object.keys[i]->literal);
    printf_json_value(*(object.values[i]), level);
  }
  insert_spaces(level);
  printf("}\n");
}

void printf_array(struct json_array_t array, uint8_t level) {
  printf("[\n");
  for (int i=0; i<array.size; ++i) {
    insert_spaces(level+INC);
    printf_json_value(*(array.elements[i]), level);
  }
  insert_spaces(level);
  printf("]\n");
}

void printf_json_value(struct json_value_t json_value, uint8_t level) {
  switch(json_value.type) {
    case J_STRING:
      printf("%s\n", ((struct json_string_t*)(json_value.data))->literal);
      break;
    case J_BOOL:
      printf("%s\n", ((struct json_bool_t*)(json_value.data))->boolean ? "true" : "false");
      break;
    case J_NUMBER:
      struct json_number_t *number=(struct json_number_t*)(json_value.data);
      printf("%s%s.%se%s%s (%s)\n",
	number->number_sign ? "-" : "+"
        ,number->digits
	, number->fraction == NULL ? "0" : number->fraction
	, number->exp_sign ? "-" : "+"
	, number->exp == NULL ? "0" : number->exp
	, number->number_sign == true ? "negative" : "positive"
      );
      break;
    case J_OBJECT:
      printf_object(*(struct json_object_t*)(json_value.data), level+2);
      break;
    case J_ARRAY:
      printf_array(*(struct json_array_t*)(json_value.data), level+2);
      break;
    default:
      exit(67);
  }
}

void free_json_string(struct json_string_t *string) {
  free(string->literal);
  free(string);
}

void free_json_bool(struct json_bool_t *boolean) {
  free(boolean);
}

void free_json_number(struct json_number_t *number) {
  if (number->digits) free(number->digits);
  if (number->fraction) free(number->fraction);
  if (number->exp) free(number->exp);
  free(number);
}

void free_json_value(struct json_value_t *value) {
  switch(value->type) {
    case J_STRING:
      free_json_string((struct json_string_t*)value->data);
      break;
    case J_BOOL:
      free_json_bool((struct json_bool_t*)value->data);
      break;
    case J_NUMBER:
      free_json_number((struct json_number_t*)value->data);
      break;
    case J_OBJECT:
      free_json_object((struct json_object_t*)value->data);
      break;
    case J_ARRAY:
      free_json_array((struct json_array_t*)value->data);
      break;
    default:
      exit(67);
  }
  free(value); 
}

void free_json_array(struct json_array_t *array) {
  for (int i=0; i<array->size; ++i) {
    free_json_value(array->elements[i]);
  }
  free(array);
}


void free_json_object(struct json_object_t *object) {
  for (int i=0; i<object->size; ++i) {
    free_json_string(object->keys[i]);
    free_json_value(object->values[i]);
  }
  free(object->keys);
  free(object->values);
  free(object);
}

char *json_value_type_to_string(enum json_value_type_t type) {
  switch(type) {
    case J_BOOL:
      return "J_BOOL";
    case J_OBJECT:
      return "J_OBJECT";
    case J_ARRAY:
      return "J_ARRAY";
    case J_STRING:
      return "J_STRING";
    case J_NUMBER:
      return "J_NUMBER";
    default:
      exit(29);
  }
}

struct json_bool_t *create_json_bool(bool boolean) {
  struct json_bool_t *json_bool=malloc(sizeof(struct json_bool_t));
  json_bool->boolean=boolean;
  return json_bool;
}

struct json_string_t *create_json_string(char *string, size_t size) {
  struct json_string_t *json_string=malloc(sizeof(struct json_string_t));
  json_string->size=size;
  json_string->literal=malloc(sizeof(char) * (size+1));
  strcpy(json_string->literal, string);
  return json_string;
}

struct json_value_t *create_json_value(void *value, enum json_value_type_t type) {
  struct json_value_t *json_value=malloc(sizeof(struct json_value_t));
  json_value->data=value;
  json_value->type=type;
  return json_value;
}

struct json_string_t *create_string_value(char *string, size_t size) {
  struct json_string_t *result=malloc(sizeof(struct json_string_t));
  result->literal=malloc(sizeof(char) * (size+1));
  result->size = size;
  strcpy(result->literal, string);
  return result;
}
