# CXX = g++
# CXXFLAGS = -Wall -Wextra -std=c++17
# TARGET = kosaraju

# all: $(TARGET)

# $(TARGET): kosaraju.cpp
#     $(CXX) $(CXXFLAGS) -o $(TARGET) kosaraju.cpp

# clean:
#     rm -f $(TARGET)

# help:
# 	@echo "make            : compila"
# 	@echo "make clean      : remove binários"

# .PHONY: all clean help



# Nome do compilador e flags comuns
CXX       := g++
CXXFLAGS  := -Wall -Wextra -std=c++17 -O2

# Nome do binário (altere conforme a pasta: dijkstra, kosaraju, prim, kruskal, bellman)
TARGET    := kosaraju

# Fonte e objeto
SRC       := $(TARGET).cpp
OBJ       := $(TARGET).o

.PHONY: all clean help

all: $(TARGET)

# Regra de link edição de objeto para binário
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra de compilação de .cpp para .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(TARGET) $(OBJ)

help:
	@echo "Uso do Makefile em $(TARGET)/"
	@echo "  make         : compila o binário '$(TARGET)'"
	@echo "  make clean   : remove binário e objetos"
	@echo "  make help    : esta mensagem"
