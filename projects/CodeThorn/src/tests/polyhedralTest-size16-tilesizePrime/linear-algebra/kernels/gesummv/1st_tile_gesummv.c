#   define N ARRAYSIZE
# define _PB_N ARRAYSIZE
/**
 * gesummv.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int n = 16;
/* Variable declaration/allocation. */
  double alpha;
  double beta;
  double A[16][16];
  double B[16][16];
  double tmp[16];
  double x[16];
  double y[16];
  int i;
  int j;
  
#pragma scop
{
    int c2;
    int c1;
    int c4;
#pragma omp parallel for private(c4)
    for (c1 = 0; c1 <= 2; c1++) {
#pragma ivdep
#pragma vector always
#pragma simd
      for (c4 = 7 * c1; c4 <= ((15 < 7 * c1 + 6?15 : 7 * c1 + 6)); c4++) {
        y[c4] = 0;
      }
    }
#pragma omp parallel for private(c4, c2)
    for (c1 = 0; c1 <= 2; c1++) {
      for (c2 = 0; c2 <= 15; c2++) {
#pragma ivdep
#pragma vector always
#pragma simd
        for (c4 = 7 * c1; c4 <= ((15 < 7 * c1 + 6?15 : 7 * c1 + 6)); c4++) {
          y[c4] = B[c4][c2] * x[c2] + y[c4];
        }
      }
    }
#pragma omp parallel for private(c4)
    for (c1 = 0; c1 <= 2; c1++) {
#pragma ivdep
#pragma vector always
#pragma simd
      for (c4 = 7 * c1; c4 <= ((15 < 7 * c1 + 6?15 : 7 * c1 + 6)); c4++) {
        tmp[c4] = 0;
      }
    }
#pragma omp parallel for private(c4, c2)
    for (c1 = 0; c1 <= 2; c1++) {
      for (c2 = 0; c2 <= 15; c2++) {
#pragma ivdep
#pragma vector always
#pragma simd
        for (c4 = 7 * c1; c4 <= ((15 < 7 * c1 + 6?15 : 7 * c1 + 6)); c4++) {
          tmp[c4] = A[c4][c2] * x[c2] + tmp[c4];
        }
      }
    }
#pragma omp parallel for private(c4)
    for (c1 = 0; c1 <= 2; c1++) {
#pragma ivdep
#pragma vector always
#pragma simd
      for (c4 = 7 * c1; c4 <= ((15 < 7 * c1 + 6?15 : 7 * c1 + 6)); c4++) {
        y[c4] = alpha * tmp[c4] + beta * y[c4];
      }
    }
  }
  
#pragma endscop
  return 0;
}
