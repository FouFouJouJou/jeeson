#include <stdio.h>
#include <stdlib.h>
#include <json.h>
#include <api.h>

int main(int argc, char **args) {
  if(argc != 2) {
    exit(80);
  }
  struct json_object_t *object=json_to_object(args[1]);
  //printf_object(*object, 0);
  printf("%d\n", get_bool(object, "kind"));
  printf("%d\n", get_int(object, "xxxx"));
  printf_object(*get_object(object, "pageInfo"), 0);
  printf("%d\n", get_int(get_object(object, "pageInfo"), "totalResults"));
  printf_object(*get_array_object_element(object, "items", 0), 0);
  // printf("%d\n", get_int(get_array_object_element(object, "items", 0), "xxxx"));
  free_json_object(object);
  return EXIT_SUCCESS;
}
