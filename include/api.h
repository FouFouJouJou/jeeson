#ifndef __API_H__
#define __API_H__

#include <stdbool.h>
#include <json.h>

#define INT(x) ((struct json_int_t *)(x))->value
#define STRING(x) ((struct json_string_t *)(x))->literal
#define ARRAY(x) ((struct json_array_t *)(x))
#define OBJECT(x) ((struct json_object_t *)(x))
#define VALUE_TO_INT(x) INT(x->data)
#define VALUE_TO_STRING(x) STRING(x->data)
#define VALUE_TO_ARRAY(x) ARRAY(x->data)
#define VALUE_TO_OBJECT(x) OBJECT(x->data)

struct json_object_t *json_to_object(char *file_name);
void free_json(struct json_object_t *object);

int get_int(struct json_object_t *object, char *key);
char *get_string(struct json_object_t *object, char *key);
struct json_object_t *get_object(struct json_object_t *object, char *key);
struct json_array_t *get_array(struct json_object_t *object, char *key);
struct json_object_t *get_array_object_element(struct json_object_t *object, char *key, uint8_t idx);
int get_array_int_element(struct json_object_t *object, char *key, uint8_t idx);
#endif
