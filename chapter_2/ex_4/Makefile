CC=gcc
CFLAGS=-Wall -g -Werror

SRC_DIR=src
OBJ_DIR=obj
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

BIN=run

all: $(BIN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): main.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(BIN) $(OBJ)

