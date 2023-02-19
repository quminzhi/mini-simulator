# OS Mini Simulator

## Description

OS Mini Simulator is a simplest emulator for a simple abstract machine with CPU and
memory. The purpose of this project is to give OSer a general idea of how
a computer system works and to serve as a reference for programers to organize a
project in a structural way and write concise, readable, and self-explanary
codes.

> The **FIRST RULE** of programming: machine is always right, and a code without testing is always wrong. 

This project is inspired from ![NEMU project](https://github.com/NJU-ProjectN/nemu).

## Configuration

OS Mini Simulator (an 8-bit addressing system) consists of instruction set
architecture (ISA), registers, and memory.

- ISA: contains 4 basic instructions shown as follows.
	
```c
// intel flavor:

        7 6 5 4    3 2 1 0
MOV    [0 0 0 0]  [RT] [RS]
ADD    [0 0 0 1]  [RT] [RS]
LOAD   [1 1 1 0]  [ ADDR  ]
STORE  [1 1 1 1]  [ ADDR  ]

RT: register target
RS: register source
LOAD: load data from memory to RA
STORE: write data from RA to memory
```

- Registers: there are 5 (8-bit) registers, `PC` (`rip` instruction pointer) and 4 general registers (`RA`, `R1`, `R2`, `R3`).

- Memory: has the size of 16 bytes and word size is 8-bit.

Basically, the simulator is an infinite while loop and only does three things,
**fetching**, **decoding**, and **execution**.

Notice that the size of memory is 16 bytes (128 bits) and word size is 8 bits. We
have basic block with index from 0 to 15. 4 bits (2^4) is required to address 16-byte
physic memory. There are 4 general purpose registers and thereby 2 bits are enough
to index them.

## Architecture

### Module Organization

- `semu.h`: general declaration and definition including registers and memory
- `semu.c`: contains data initialization, a BIG while loop of fetching, decoding and executing instructions,
	and an exit handler.
- `dec_exec.c`: a submodule used in `semu.c`. (`struct inst` is specific to
	the submodule, so we put it in `dec_exec.c` instead of general declaration
	in `semu.h`).
- `test.c`: tests the integrity and correctness of the code (meta programming).
- `Makefile`: includes an automatic building system.

```bash
.
├── Makefile
├── README.md
├── ref
│   └── bit-field.c  # test for C bit field
└── src
    ├── dec-exec.c
    ├── semu.c
    ├── semu.h
    └── test.c
```

## Testing

Test code is written in meta programming, making the code readable and concise.
`TESTCASES` contains test cases and each test case is handled by `MAKETEST`.

```c
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
```

## Summary

Contact:

Bug reports and suggestions please go to Minzhi (matt.0xcc@gmail.com).

This project is restricted to ![GNU General Public License 3.0 (GPL 3.0)](https://opensource.org/licenses/GPL-3.0).
