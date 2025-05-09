CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = kosaraju

all: $(TARGET)

$(TARGET): kosaraju.cpp
    $(CXX) $(CXXFLAGS) -o $(TARGET) kosaraju.cpp

clean:
    rm -f $(TARGET)

help:
	@echo "make            : compila"
	@echo "make clean      : remove binários"

.PHONY: all clean help