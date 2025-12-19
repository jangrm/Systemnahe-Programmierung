# Compiler & Flags
CC      := gcc
CFLAGS  := -Wall -Wextra -Wpedantic -std=c11 -g
LDFLAGS :=
TARGET  := sopfind

# Directories
SRC_DIR := src
OBJ_DIR := build

# Sources & Objects
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build dir if missing
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Test (placeholder for now)
test:
	@echo "No tests yet."

.PHONY: all clean test
