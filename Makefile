# Makefile - Projeto ordenacao-C
# Autor: OkokoMug
# Licença: MIT

CC = gcc
CFLAGS = -Wall -Wextra -O2

SRC_DIR = src
BIN_DIR = bin
DATA_DIR = data

TARGET = $(BIN_DIR)/ordenacao

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/csv.c \
       $(SRC_DIR)/filtros.c \
       $(SRC_DIR)/ordenacao.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	$(TARGET)

clean:
	rm -f $(SRC_DIR)/*.o
	rm -rf $(BIN_DIR)

rebuild: clean all

# Informações de ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make         - Compila o projeto"
	@echo "  make run     - Compila e executa o programa"
	@echo "  make clean   - Remove binários e objetos"
	@echo "  make rebuild - Limpa e recompila tudo"
