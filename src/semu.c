#include "semu.h"
#include <stdio.h>     // it is not recommended to include stdio in common header file
#include <string.h>

// hardcode instruction in memory
u8 R[REG_SIZE], M[MEM_SIZE] = {
	0b11100111,
	0b00000100,
	0b11100110,
	0b00010001,
	0b11111000,
	0b00000000,
	0b00010000,
	0b00100001,
	0b00000000,
};

static void init_regs() {
	// initialize regs with 0s
	memset(R, 0x0, sizeof(u8) * REG_SIZE);
	pc = 0;   // redundant but clear
}

static void print_memory() {
	for (int i = 0; i < MEM_SIZE; i++) {
		printf("M[%02d] = %02x (%d)\n", i, M[i], M[i]);
	}
}

void start_loop() {
	while (1) {
		if (M[pc] == 0x0) {
			// exception: exit instruction 0x00
			printf("Hit GOOD trap, cool ~\n");
			print_memory();
			break;
		} else {
			dec_exec();
		}
	}
}

int main(int argc, char *argv[]) {
	
	init_regs();
	start_loop();
	
	return 0;
}
