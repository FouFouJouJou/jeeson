#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <io.h>

size_t read_from_file(char *file_name, char **buff) {
  FILE *fd=fopen(file_name, "rb");
  fseek(fd, 0L, SEEK_END);
  size_t size=ftell(fd);
  *buff=malloc(sizeof(char)*size);
  rewind(fd);
  size_t bytes_read=fread(*buff, sizeof(char), size, fd);
  if (bytes_read != size) {
    fprintf(stderr, "[ERROR]: file was not read fully!");
    fclose(fd);
    exit(6);
  }
  fclose(fd);
  return size;
}
