CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = 
INCLUDE_DIR = include 

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o,$(SRCS))
EXEC = $(BIN_DIR)/disp-header

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $^

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)