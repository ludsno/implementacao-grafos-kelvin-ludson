# Nome do executável
TARGET = kruskal.bin

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Arquivos fonte
SRC = kruskal.cpp

# Regra padrão
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Limpeza dos arquivos gerados
clean:
	rm -f $(TARGET)

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
