# Makefile para o Trabalho Prático 1

# Nome do executável
EXEC = tp1

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -std=c++17

# Arquivos objeto
OBJ = main.o grafo.o

# Regra padrão
all: $(EXEC)

# Regra para gerar o executável
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

# Compila main.cpp
main.o: main.cpp grafo.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compila grafo.cpp
grafo.o: grafo.cpp grafo.hpp
	$(CXX) $(CXXFLAGS) -c grafo.cpp

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)

# Regra para rodar o programa com um arquivo de entrada
run: $(EXEC)
	./$(EXEC) < testCase01.txt
