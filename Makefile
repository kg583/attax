
CC = gcc
CFLAGS = -O3 -Wall -Wextra -Wpedantic

TARGET = attax

all: $(TARGET)

$(TARGET): main.c exec.h ops.c params.h state.h
	$(CC) $(CFLAGS) main.c ops.c -o $(TARGET)

clean:
	rm $(TARGET)

.PHONY: all clean