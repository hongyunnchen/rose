#   define NI ARRAYSIZE
#   define NJ ARRAYSIZE
#   define NK ARRAYSIZE
#   define NL ARRAYSIZE
# define _PB_NI ARRAYSIZE
# define _PB_NJ ARRAYSIZE
# define _PB_NK ARRAYSIZE
# define _PB_NL ARRAYSIZE
/**
 * 2mm.c: This file is part of the PolyBench/C 3.2 test suite.
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
  int ni = 16;
  int nj = 16;
  int nk = 16;
  int nl = 16;
/* Variable declaration/allocation. */
  double alpha;
  double beta;
  double tmp[16][16];
  double A[16][16];
  double B[16][16];
  double C[16][16];
  double D[16][16];
  int i;
  int j;
  int k;
  
#pragma scop
{
    int c7;
    int c2;
    int c1;
    int c5;
    int c10;
#pragma omp parallel for private(c10, c2, c7)
    for (c1 = 0; c1 <= 2; c1++) {
      for (c2 = 0; c2 <= 2; c2++) {
        for (c7 = 7 * c2; c7 <= ((15 < 7 * c2 + 6?15 : 7 * c2 + 6)); c7++) {
#pragma ivdep
#pragma vector always
#pragma simd
          for (c10 = 7 * c1; c10 <= ((15 < 7 * c1 + 6?15 : 7 * c1 + 6)); c10++) {
            D[c10][c7] *= beta;
          }
        }
        for (c7 = 7 * c2; c7 <= ((15 < 7 * c2 + 6?15 : 7 * c2 + 6)); c7++) {
#pragma ivdep
#pragma vector always
#pragma simd
          for (c10 = 7 * c1; c10 <= ((15 < 7 * c1 + 6?15 : 7 * c1 + 6)); c10++) {
            tmp[c10][c7] = 0;
          }
        }
      }
    }
#pragma omp parallel for private(c10, c5, c2, c7)
    for (c1 = 0; c1 <= 2; c1++) {
      for (c2 = 0; c2 <= 2; c2++) {
        for (c5 = 0; c5 <= 15; c5++) {
          for (c7 = 7 * c2; c7 <= ((15 < 7 * c2 + 6?15 : 7 * c2 + 6)); c7++) {
#pragma ivdep
#pragma vector always
#pragma simd
            for (c10 = 7 * c1; c10 <= ((15 < 7 * c1 + 6?15 : 7 * c1 + 6)); c10++) {
              tmp[c10][c7] += alpha * A[c10][c5] * B[c5][c7];
            }
          }
        }
        for (c5 = 0; c5 <= 15; c5++) {
          for (c7 = 7 * c2; c7 <= ((15 < 7 * c2 + 6?15 : 7 * c2 + 6)); c7++) {
#pragma ivdep
#pragma vector always
#pragma simd
            for (c10 = 7 * c1; c10 <= ((15 < 7 * c1 + 6?15 : 7 * c1 + 6)); c10++) {
              D[c10][c5] += tmp[c10][c7] * C[c7][c5];
            }
          }
        }
      }
    }
  }
  
#pragma endscop
  return 0;
}
