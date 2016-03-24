#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {
  size_t n, str_len = 0;
  const char *str = "foobar";
  char *str_cpy = malloc(1024);
  srand(time(NULL));
  /* First we create some random data. 
   * Lets assume this is our binary stream */
  n = 0;
  while(n++ < 1024) {
    str_cpy[n] = rand() % 255;
  }
  /* We have a knowns string we want to print */
  printf("%s\n", str);
  /* Ooops we forgot to copy the null terminator on the following line! */ 
  memcpy(str_cpy, str, 6);
  str_len = strlen(str_cpy);
  /* This is unlikely to print 6 */
  printf("%zu\n", str_len);
  /* This is undefined behaviour */
  printf("%s\n", str_cpy);
  return 0;
}

