CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = dijkstra.bin

SRC = dijkstra.cpp

.PHONY: all clean help

all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

help:
	@echo "Uso: make [all|clean|help]"
	@echo "  make       : compila '$(TARGET)'"
	@echo "  make clean : remove o binário"
	@echo "  make help  : esta mensagem"
