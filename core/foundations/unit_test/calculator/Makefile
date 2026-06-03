CC       = gcc
CFLAGS   = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS  = $(shell pkg-config --cflags --libs criterion)

SRC_DIR  = src
TEST_DIR = test
OBJ_DIR  = obj
BIN_DIR  = bin

SRC      = $(SRC_DIR)/calculator.c
TEST_SRC = $(TEST_DIR)/calculator_test.c
OBJ      = $(OBJ_DIR)/calculator.o
TEST_OBJ = $(OBJ_DIR)/calculator_test.o
TEST_BIN = $(BIN_DIR)/run_tests

.PHONY: all build test clean

all: test

build: $(OBJ_DIR) $(BIN_DIR) $(OBJ)

test: $(OBJ_DIR) $(BIN_DIR) $(TEST_BIN)
	./$(TEST_BIN)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/calculator.o: $(SRC) include/calculator.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/calculator_test.o: $(TEST_DIR)/calculator_test.c include/calculator.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(TEST_BIN): $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
