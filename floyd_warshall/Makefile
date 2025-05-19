# Nome do compilador e flags comuns
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Nome do binário
TARGET = floyd_warshall.bin

# Fonte e objeto
SRC = floyd_warshall.cpp

.PHONY: all clean help

all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	@rm -f $(TARGET)

help:
	@echo "Uso: make [all|clean|help]"
	@echo "  make       : compila '$(TARGET)'"
	@echo "  make clean : remove o binário"
	@echo "  make help  : esta mensagem"