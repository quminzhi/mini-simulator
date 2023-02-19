#include <stdint.h>

typedef uint8_t u8;

#define MEM_SIZE 16

// trick: size of registers
enum {RA, R1, R2, R3, PC, REG_SIZE};   
// #define RA 0
// #define R1 1
// ...
// #define REG_SIZE 5

// trick: enclose c array in struct so that we can delay to assign value
extern u8 M[MEM_SIZE], R[REG_SIZE];

#define pc R[PC]   // alias to R[PC]

void dec_exec();  // declared here and implemented in the submodule
