CC       = gcc
CFLAGS   = -Wall -Wextra -std=c99
LDFLAGS  = $(shell pkg-config --cflags --libs criterion)

TEST_DIR = test
OBJ_DIR  = obj
BIN_DIR  = bin

TEST_SRC = $(TEST_DIR)/data_structures_basics_test.c
TEST_OBJ = $(OBJ_DIR)/data_structures_basics_test.o
TEST_BIN = $(BIN_DIR)/run_tests

.PHONY: all build test clean

all: test

build: $(OBJ_DIR) $(BIN_DIR) $(TEST_OBJ)

test: $(OBJ_DIR) $(BIN_DIR) $(TEST_BIN)
	./$(TEST_BIN)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/data_structures_basics_test.o: $(TEST_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TEST_BIN): $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
