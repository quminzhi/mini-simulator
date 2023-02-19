#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semu.h"

u8 R[REG_SIZE], M[MEM_SIZE], oldR[REG_SIZE], oldM[MEM_SIZE], *newM = M, *newR = R;   // newR and newM are alias to R and M

// rand() return a int value (4 bytes)
void rand_init_mem_reg() {
  for (int i = 0; i < REG_SIZE; i++) {
    oldR[i] = rand() & 0xff;
  }
  for (int i = 0; i < MEM_SIZE; i++) {
    oldM[i] = rand() & 0xff;
  }
}

#define ASSERT_EQ(a, b) ((u8)a == (u8)b)

// each line corresponds a block of codes defined in MAKETEST
// R[0]: RA
#define TESTCASES(_) \
  _(1, 0b11100111, rand_init_mem_reg, ASSERT_EQ(newR[0], oldM[7])) \
  _(2, 0b00000100, rand_init_mem_reg, ASSERT_EQ(newR[1], oldR[0])) \
  _(3, 0b11100101, rand_init_mem_reg, ASSERT_EQ(newR[0], oldM[5]) ) \
  _(4, 0b00010001, rand_init_mem_reg, ASSERT_EQ(newR[0], oldR[0] + oldR[1]) ) \
  _(5, 0b11110111, rand_init_mem_reg, ASSERT_EQ(newM[7], oldR[0]) ) 

// note #inst in printf 
#define MAKETEST(id, inst, init, postcond) { \
  init(); \
  memcpy(oldM, M, MEM_SIZE); \
  memcpy(oldR, R, REG_SIZE); \
  pc = 0; M[pc] = inst; \
  dec_exec(); \
  printf("Test #%d (%s): %s\n", \
      id, #inst, (postcond) ? "PASS" : "FAIL"); \
}

int main(int argc, char *argv[]) {
  TESTCASES(MAKETEST)
  return 0;
}
