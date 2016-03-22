#include <stdio.h>
#include <string.h>
#include <stdlib.h>

  int main(void) {
    int i = 0;
    printf("c1 c2 c3 c4 c5 c6 c7 c8 c9 c0\n");
      for(i = 0; i < 10; i++) {
      printf("%0.2d %0.2d %0.2d %0.2d %0.2d %0.2d %0.2d %0.2d %0.2d %0.2d\n",
          i, 
          i + 1, 
          i + 2, 
          i + 3,
          i + 4,
          i + 5,
          i + 6,
          i + 7,
          i + 8,
          i + 9
          );
    }
  }

