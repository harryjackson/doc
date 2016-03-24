#include <stdio.h>
#include <string.h>

int main(void) {
  size_t i = 0;
  /* @bug: 5 characters in an array that can take 6 */
  char str[6] = "tortug";
  printf("compare = %d\n", strncmp(str, "tortuga", 6));
  for(i = 0; i < 6; i++) {
    printf("char at %zu == %c\n", i, str[i]);
  }
}
