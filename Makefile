
CC = gcc
CFLAGS = -O3 -Wall -Wextra -Wpedantic

TARGET = attax

all: $(TARGET)

$(TARGET): main.c ops.c params.h state.h
	$(CC) $(CFLAGS) main.c ops.c -o $(TARGET) -lm

clean:
	$(RM) $(TARGET)

run:
	$(MAKE) clean
	$(MAKE) $(TARGET)
	./$(TARGET)

.PHONY: all clean run
