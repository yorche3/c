CC       = gcc
CFLAGS   = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS  = $(shell pkg-config --cflags --libs criterion)

SRC_DIR  = src
TEST_DIR = test
OBJ_DIR  = obj
BIN_DIR  = bin

SRC      = $(SRC_DIR)/naive_sort.c
TEST_SRC = $(TEST_DIR)/naive_sort_test.c
OBJ      = $(OBJ_DIR)/naive_sort.o
TEST_OBJ = $(OBJ_DIR)/naive_sort_test.o
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

$(OBJ_DIR)/naive_sort.o: $(SRC) include/naive_sort.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/naive_sort_test.o: $(TEST_SRC) include/naive_sort.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(TEST_BIN): $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
