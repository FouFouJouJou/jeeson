#include <stdio.h>
#include <stdlib.h>
#include <json.h>
#include <api.h>

int main(void) {
  char *file_name="../files/sample.json";
  struct json_object_t *object=json_to_object(file_name);
  //printf_object(*object, 0);
  //printf("%s\n", get_string(object, "kind"));
  //printf("%d\n", get_int(object, "xxxx"));
  //printf_object(*get_object(object, "pageInfo"), 0);
  //printf("%d\n", get_int(get_object(object, "pageInfo"), "totalResults"));
  //printf_object(*get_array_object_element(object, "items", 0), 0);
  //printf_object(*get_array_int_element(object, "items", 0), 0);
  //array_map(get_array_(object, "items"), printf, get_method)
  free_json_object(object);
  return EXIT_SUCCESS;
}
