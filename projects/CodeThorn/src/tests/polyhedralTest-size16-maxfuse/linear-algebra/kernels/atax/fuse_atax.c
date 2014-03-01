#   define NX ARRAYSIZE
#   define NY ARRAYSIZE
# define _PB_NX ARRAYSIZE
# define _PB_NY ARRAYSIZE
/**
 * atax.c: This file is part of the PolyBench/C 3.2 test suite.
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
  int nx = 16;
  int ny = 16;
  double A[16][16];
  double x[16];
  double y[16];
  double tmp[16];
  int i;
  int j;
  
#pragma scop
{
    int c0;
    int c3;
    for (c0 = 0; c0 <= 15; c0++) {
      tmp[c0] = 0;
      for (c3 = 0; c3 <= 15; c3++) {
        tmp[c0] = tmp[c0] + A[c0][c3] * x[c3];
      }
      y[c0] = 0;
      for (c3 = 0; c3 <= c0; c3++) {
        y[c0 + -1 * c3] = y[c0 + -1 * c3] + A[c3][c0 + -1 * c3] * tmp[c3];
      }
    }
    for (c0 = 16; c0 <= 30; c0++) {
      for (c3 = c0 + -15; c3 <= 15; c3++) {
        y[c0 + -1 * c3] = y[c0 + -1 * c3] + A[c3][c0 + -1 * c3] * tmp[c3];
      }
    }
  }
  
#pragma endscop
  return 0;
}
