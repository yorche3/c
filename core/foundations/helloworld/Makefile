CC       = gcc
CFLAGS   = -Wall -Wextra -std=c99
TARGET   = hello_world
SRC      = hello_world.c
OBJ      = hello_world.o

.PHONY: all build run clean

all: build

build: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)
