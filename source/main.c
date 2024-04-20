#include <stdio.h>
#include <stdlib.h>
#include <token.h>
#include <lexer.h>
#include <io.h>
#include <parser.h>

int main(int argc, char **args) {
  if(argc != 2) {
    exit(80);
  }

  struct token_t **tokens=0;
  char *buff=0;
  size_t size=read_from_file(args[1], &buff);
  printf_object(*parse(buff, size), 0);
  free(buff);

  //printf_tokens(tokens, token_size, printf_token);

  //struct json_object_t *object=json_to_object(args[1]);
  //printf_object(*object, 0);
  //printf_array(*get_array(object, "items"), 0);
  //printf("%d\n", get_int(get_array_object_element(object, "items", 0), "xxxx"));
  //free_json_object(object);
  return EXIT_SUCCESS;
}
