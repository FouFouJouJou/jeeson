#include <stdio.h>
#include <stdlib.h>
#include <token.h>
#include <lexer.h>
#include <io.h>
#include <parser.h>
#include <json.h>

int main(int argc, char **args) {
  if (argc != 2) {
    exit(80);
  }
  struct json_object_t *object=json_to_object(args[1]);
  struct json_array_t *array = get_array(object, "items");
  free_json_object(object);
  return EXIT_SUCCESS;
}
