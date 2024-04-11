#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <io.h>

size_t read_from_file(char *file_name, char **buff) {
  struct stat stats;
  stat(file_name, &stats);
  size_t size=stats.st_size;
  *buff=malloc(sizeof(char)*size);
  int fd=open(file_name, O_RDONLY);
  size_t bytes_read=read(fd, *buff, size);
  close(fd);
  return bytes_read;
}
