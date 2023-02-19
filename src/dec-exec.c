#include "semu.h"
#include <assert.h>

// refer to c bit fields: little endian like
typedef union inst {
	struct { u8 rs : 2, rt : 2, op : 4; } rtype;   // register type: [ op rt rs ]
	struct { u8 addr : 4,       op : 4; } mtype;   //   memory type: [ op addr ]
} inst_t;

// parse with meta programming
#define RTYPE(x) u8 rt = (x)->rtype.rt, rs = (x)->rtype.rs;
#define MTYPE(x) u8 addr = (x)->mtype.addr;

void dec_exec() {
	inst_t *cur = (inst_t *)&M[pc];  // or (inst_t *)(M + pc)
	switch (cur->rtype.op) {         // or cur->mtype.op
		case 0b0000: { RTYPE(cur); R[rt] = R[rs];   pc++; break; }
		case 0b0001: { RTYPE(cur); R[rt] += R[rs];  pc++; break; }
		case 0b1110: { MTYPE(cur); R[RA] = M[addr]; pc++; break; }
		case 0b1111: { MTYPE(cur); M[addr] = R[RA]; pc++; break; }
		default: assert(0);  // cur->op == 0, 0b00000000 (exit instruction)
	}
}
