BIN = semu

BUILD_DIR = ./build
SRC_DIRS = ./src
TEST_DIR = ./test

# find all c files and header files
SRCS = $(shell find $(SRC_DIRS) -name '*.c')

# string substitution for object files
# % match files in SRC, and turn each one into ./build/*.c.o, % is *.c
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)

# include source directories so that *.h file can be found 
INC_DIRS = $(shell find $(SRC_DIRS) -type d)
# add prefix '-I' to INC_DIRS
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Compilation Settings

CC = gcc
# C compiler flags, -MMD -MP generate .d makefile
CCFLAGS = $(INC_FLAGS) -MMD -MP
CFLAGS = -Wall -Werror -std=c11 -O2 -g
LD = gcc
LDFLAGS = 


$(BUILD_DIR)/$(BIN): $(OBJS)
	$(LD) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: run test clean
run: $(BUILD_DIR)/$(BIN)
	$(BUILD_DIR)/$(BIN)
# rely on dec-exec.c.o
test: $(BUILD_DIR)/$(BIN)
	mkdir -p $(BUILD_DIR)/test
	$(CC) $(CCFLAGS) $(CFLAGS) -c $(TEST_DIR)/test.c -o $(BUILD_DIR)/test/test.c.o 
	$(LD) $(BUILD_DIR)/test/test.c.o $(BUILD_DIR)/src/dec-exec.c.o -o $(BUILD_DIR)/test/test
	$(BUILD_DIR)/test/test

clean:
	rm -rf $(BUILD_DIR)
