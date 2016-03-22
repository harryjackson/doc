#include <stdio.h>
#include <string.h>

int main(void) {
  char str[6] = "tortug";//5 characters in an array that can take 6
  printf("compare = %d\n", strncmp(str, "tortuga", 6));
  size_t i = 0;
  for(i = 0; i < 6; i++) {
    printf("char at %zu == %c\n", i, str[i]);
  }
}
