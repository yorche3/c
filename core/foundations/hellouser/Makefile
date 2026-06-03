CC       = gcc
CFLAGS   = -Wall -Wextra -std=c99
TARGET   = hello_user
SRC      = hello_user.c
OBJ      = hello_user.o

.PHONY: all build run clean

all: build

build: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)
