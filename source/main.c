#include <stdio.h>
#include <stdlib.h>
#include <token.h>
#include <lexer.h>
#include <io.h>
#include <parser.h>
#include <api.h>

int main(int argc, char **args) {
  if(argc != 2) {
    exit(80);
  }
  struct json_object_t *object=json_to_object(args[1]);
  printf_object(*object, 0);
  free_json_object(object);
  return EXIT_SUCCESS;
}
