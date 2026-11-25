
CXX = gcc
CXXFLAGS = -O3 -Wall -Wextra -Wpedantic

TARGET = attax

all: $(TARGET)

$(TARGET): main.cpp ops.cpp params.h state.h
	$(CXX) $(CXXFLAGS) main.cpp ops.cpp -o $(TARGET) -lm

clean:
	$(RM) $(TARGET)

run:
	$(MAKE) clean
	$(MAKE) $(TARGET)
	./$(TARGET)

.PHONY: all clean run
