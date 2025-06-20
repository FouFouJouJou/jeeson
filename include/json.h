#ifndef __JSON_H__
#define __JSON_H__
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BOOL(x) ((struct json_bool_t *)(x))->boolean
#define STRING(x) ((struct json_string_t *)(x))->literal
#define ARRAY(x) ((struct json_array_t *)(x))
#define OBJECT(x) ((struct json_object_t *)(x))
#define NUMBER(x) ((struct json_number_t *)(x))
#define VALUE_TO_STRING(x) STRING(x->data)
#define VALUE_TO_ARRAY(x) ARRAY(x->data)
#define VALUE_TO_OBJECT(x) OBJECT(x->data)
#define VALUE_TO_BOOL(x) BOOL(x->data)
#define VALUE_TO_NUMBER(x) NUMBER(x->data)

enum json_value_type_t {
  J_OBJECT
  ,J_ARRAY
  ,J_STRING
  ,J_NUMBER
  ,J_BOOL
};

struct json_number_t {
  char *digits;
  char *fraction;
  char *exp;

  /* true => negative, false => positive */
  bool number_sign;
  bool exp_sign;
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

ssize_t has_key(struct json_object_t *object, char *key);
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

struct json_object_t *json_to_object(char *file_name);
void free_json(struct json_object_t *object);

struct json_object_t *get_object(struct json_object_t *object, char *key);
double get_number(struct json_object_t *object, char *key);
char *get_string(struct json_object_t *object, char *key);
bool get_bool(struct json_object_t *object, char *key);
struct json_array_t *get_array(struct json_object_t *object, char *key);

double get_array_number_element(struct json_array_t *arr, uint8_t idx);
bool get_array_boolean_element(struct json_array_t *arr, uint8_t idx);
char *get_array_string_element(struct json_array_t *arr, uint8_t idx);
struct json_object_t *get_array_object_element(struct json_array_t *arr, uint8_t idx);
struct json_array_t *get_array_array_element(struct json_array_t *arr, uint8_t idx);
#endif
