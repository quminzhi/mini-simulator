#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef uint8_t u8;

// x bits <= 8 bits ==> 1 bytes
typedef struct t1 {
	u8 a : 4;
	u8 b : 2;
	u8 c : 1;
	u8 d : 1;
} t1_t;

// 9 bits > 8 bits of u8 ==> 2 bytes
typedef struct t2 {
	u8 a : 4;
	u8 b : 2;
	u8 c : 1;
	u8 d : 1;
	u8 e : 1;
} t2_t;

int main(int argc, char *argv[]) {
	
	// lab1: memory space
	printf("Size of t1_t is %ul\n", sizeof(t1_t));
	printf("Size of t2_t is %ul\n", sizeof(t2_t));

	// lab2: memory order (implementation defined by GCC or other compilers)
	t1_t foo;
	foo.a = 0b1000;
	printf("foo.a = 0b1000, the value of foo is %ul\n", foo);

	t1_t bar;
	bar.d = 0b0001;
	printf("bar.d = 0b0001, the value of bar is %ul\n", bar);

	printf("its arrangement is similar to little endian: t1 => [a b c d]\n\twhere 'a' is lowest 4 bits, followed by 2 bits for 'b', followedd by 1 bit for 'c', and followed by 1 bit for 'd' (which is the most significant bit)\n");

	return 0;
}
