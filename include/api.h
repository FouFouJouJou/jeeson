#ifndef __API_H__
#define __API_H__

#include <stdbool.h>
#include <json.h>


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
