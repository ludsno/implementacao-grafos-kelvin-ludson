TARGET = kruskal.bin

CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC = kruskal.cpp

.PHONY: all clean example help

all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

help:
	@echo "Uso: make [all|clean|example|help]"
	@echo "  make         : compila '$(TARGET)'"
	@echo "  make clean   : remove o binário"
	@echo "  make example : mostra exemplo de uso"
	@echo "  make help    : esta mensagem"

example:
	@echo ""
	@echo "Exemplo de uso do programa:"
	@echo ""
	@echo "./$(TARGET) [opções]"
	@echo ""
	@echo "  -h             : mostra o help"
	@echo "  -o <arquivo>   : redireciona a saída para o ‘arquivo’"
	@echo "  -f <arquivo>   : indica o ‘arquivo’ que contém o grafo de entrada"
	@echo "  -s             : mostra a solução"
	@echo ""
	@echo "Executando com grafo de exemplo (com e sem -s para mostrar a solução):"
	@echo ""
	./kruskal.bin -f example.dat
	./kruskal.bin -f example.dat -s
