#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if 0
  #define PRINT(a) printf a
#else
  #define PRINT(a) (void)0
#endif

/* The product of these two numbers (ROWS_N * COLS_N) must be greater than the
 * CPU Cache size or you won't see locality effects quite as well */
#define ROWS_N 100000
#define COLS_N 100

#define SWAP 0
#if SWAP
  #define ROWS ROWS_N
  #define COLS COLS_N
#else
  #define ROWS COLS_N
  #define COLS ROWS_N
#endif

static float *  matrix;
static float ** matrix2;

void bench_contig(size_t iter) {
  size_t i = 0;
  size_t r = 0;
  size_t c = 0;
  for(i = 0; i < iter ;i++) {
    for(r = 0; r < ROWS; r++) {
      PRINT(("r%zu->", r));
      for(c = 0; c < COLS; c++) {
        PRINT(("|%zu", c));
        matrix[r + r*c] = 1.0;
      }
      PRINT(("\n"));
    }
  }
}
void bench_row_contig(size_t iter) {
  size_t i = 0;
  size_t r = 0;
  size_t c = 0;
  for(i = 0; i < iter ;i++) {
    for(r = 0; r < ROWS; r++) {
      PRINT(("r%zu->", r));
      for(c = 0; c < COLS; c++) {
        PRINT(("|%zu", c));
        matrix2[r][c] = 1.0;
      }
      PRINT(("\n"));
    }
  }
}
int main(void) {
  time_t t1; 
  time_t t2; 
  double time_r   = 0.0;
  size_t iterations = 100;
  //size_t i = 0;
  size_t r = 0;
  //size_t c = 0;
  int rows    = ROWS;
  int columns = COLS;

  matrix = malloc(rows * columns * sizeof(float));

  t1 = clock();
  bench_contig(iterations);
  t2 = clock();
  time_r = difftime(t2, t1) / CLOCKS_PER_SEC;
  printf("%f secs\n",time_r);

  matrix2 = malloc(rows * sizeof(float*));
  for(r = 0; r < rows; r++) {
    matrix2[r]    = malloc(columns * sizeof(float));
  }
  
  t1 = clock();
  bench_row_contig(iterations);
  t2 = clock();
  time_r = difftime(t2, t1) / CLOCKS_PER_SEC;
  printf("%f secs\n",time_r);

  free(matrix);
  for(r = 0; r < rows; r++) {
    free(matrix2[r]);
  }
  free(matrix2);
  return 0;
}


