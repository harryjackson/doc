#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {
  srand(time(NULL));
  size_t n = 0;
  //First we create some random data. 
  //Lets assume this is our binary stream
  char *str_cpy = malloc(1024);
  n = 0;
  while(n++ < 1024) {
    str_cpy[n] = rand() % 255;
  }
  //We have a knowns string we want to print
  const char *str = "foobar";
  printf("%s\n", str);
  memcpy(str_cpy, str, 6);//Ooops we forgot to copy the null terminator 
  size_t str_len = strlen(str_cpy);
  // This is unlikely to print 6
  printf("%zu\n", str_len);
  //This is undefined behaviour
  printf("%s\n", str_cpy);
  return 0;
}

