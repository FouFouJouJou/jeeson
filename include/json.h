#ifndef __JSON_H__
#define __JSON_H__
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

enum json_value_type_t {
  J_OBJECT
  ,J_ARRAY
  ,J_STRING
  ,J_NUMBER
  ,J_BOOL
};

enum json_number_type_t {
  J_DIGITS
  ,J_FRACTION
  ,J_EXP
};

struct json_number_t {
  char *value;
  bool sign;
  enum json_number_type_t type; 
};

struct json_bool_t {
  bool boolean;
};

struct json_boolean_t {
  bool value;
};

struct json_string_t {
  char *literal;
  size_t size;
};

struct json_value_t {
  enum json_value_type_t type;
  void *data;
};

struct json_object_t {
  struct json_string_t **keys;
  struct json_value_t **values;
  size_t size;
};

struct json_array_t {
  struct json_value_t **elements;
  size_t size;
};

void printf_object(struct json_object_t object, uint8_t level);
void printf_array(struct json_array_t array, uint8_t level);
void printf_json_value(struct json_value_t json_value, uint8_t level);
struct json_int_t *create_json_int(int integet);
struct json_string_t *create_json_string(char *string, size_t size);
struct json_value_t *create_json_value(void *value, enum json_value_type_t type);
struct json_bool_t *create_json_bool(bool boolean);
void free_json_value(struct json_value_t *value);
void free_json_array(struct json_array_t *array);
void free_json_object(struct json_object_t *object);

#endif
