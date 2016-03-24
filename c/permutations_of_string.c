#include <assert.h>
#include <stdio.h>
#include <string.h>
       
#define TEN_FACTORIAL 3628800
static size_t pos = 0;
static char AllCombos[TEN_FACTORIAL][10];
void swap(char *x, char *y) {
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

void permute(char *a, int l, int r) {
  int i;
  if (l == r) {
    assert(pos <= TEN_FACTORIAL);
    memcpy(AllCombos[pos++], a, 10);

  }
  else {
    for (i = l; i <= r; i++) {
      swap((a+l), (a+i));
      permute(a, l+1, r);
      swap((a+l), (a+i));
    }
  }
}

int main(void) {
  size_t i = 0;
  char str[] = "ABCDEFGHIJ";
  int n = strlen(str);
  permute(str, 0, n-1);

  for(i = 0; i < TEN_FACTORIAL; i++) {
    printf("%.10s\n", AllCombos[i]);
  }
  return 0;
}
