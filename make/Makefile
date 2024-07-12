# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wextra 

# Directories
SRC_DIR := src
OBJ_DIR := obj 
BIN_DIR := bin 

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Include directory for header files
INC_DIR := inc 
INCLUDES := -I$(INC_DIR)

# Special targets
.PHONY: all clean

# Default target
all: $(BIN_DIR)/executable

# Rule to build the executable
$(BIN_DIR)/executable: $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to build object files 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean up generated files and directories
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)