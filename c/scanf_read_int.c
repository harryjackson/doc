#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void flush_stream();

void flush_stream() {
  char c;
  do {
    c = getchar();
  }
  while (!isdigit(c) && c != '\n');
  ungetc(c, stdin);
}

int main(void) {
  const char *prompt = "Input please: ";
  int input;            // input from user
  printf("Enter the number between 0 and 10 and I will tell you your grade!\n");
  while(1) {
    printf("%s", prompt);
    int ret = scanf("%d", &input);
    if(ret == 0) {
      printf("Sorry, invalid character data, your input must be from 0 to 10.\n");
      flush_stream();
      continue;
    }
    if(ret > 0) {
      if (input < 0 || input > 10) {   
        printf("Sorry, invalid character data, your input must be from 0 to 10.\n");
        flush_stream();
        continue;
      }

      switch (input) {                       
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
          printf("Your grade is F. \n");
          break;  
        case 6:
          printf("Your grade is D. \n");
          break;
      }
    }
  }
}
