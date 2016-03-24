#include <errno.h>
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *pattern;

int glob_err_handler(const char *path, int err_num) {
  fprintf(stderr, "%s: %s: %s\n", pattern, path, strerror(err_num));
  return 0;
}

int main(void) {
  int i;
  glob_t file_struct;
  int ret;

  pattern = "g*c";
  ret = glob(pattern, 0, glob_err_handler, &file_struct);
  if (ret != 0) {
    fprintf(stderr, "Something went bang");
    exit(1);
  }

  for (i = 0; i < file_struct.gl_pathc; i++) {
    printf("%s\n", file_struct.gl_pathv[i]);
  }

  globfree(&file_struct);
  return 0;
}
