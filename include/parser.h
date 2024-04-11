#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdlib.h>
#include <token.h>
#include <json.h>
struct json_array_t *parse_array(struct token_t ***tokens, size_t size);
struct json_object_t *parse_object(struct token_t ***tokens, size_t size);
struct json_object_t *parse(char *buff, size_t read_bytes);

#endif
