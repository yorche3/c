CC       = gcc
CFLAGS   = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS  = $(shell pkg-config --cflags --libs criterion)

SRC_DIR  = src
TEST_DIR = test
OBJ_DIR  = obj
BIN_DIR  = bin

SRC      = $(SRC_DIR)/numbers.c
TEST_SRC = $(TEST_DIR)/numbers_rec_test.c $(TEST_DIR)/numbers_ite_test.c
OBJ      = $(OBJ_DIR)/numbers.o
TEST_OBJ = $(OBJ_DIR)/numbers_rec_test.o $(OBJ_DIR)/numbers_ite_test.o
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

$(OBJ_DIR)/numbers.o: $(SRC) include/numbers.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/numbers_rec_test.o: $(TEST_DIR)/numbers_rec_test.c include/numbers.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/numbers_ite_test.o: $(TEST_DIR)/numbers_ite_test.c include/numbers.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(TEST_BIN): $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
