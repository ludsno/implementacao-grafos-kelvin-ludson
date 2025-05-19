CXX       := g++ 
CXXFLAGS  := -Wall -Wextra -std=c++17 -O2

TARGET    := kosaraju.bin

SRC       := kosaraju.cpp
OBJ       := $(SRC:.cpp=.o)
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
