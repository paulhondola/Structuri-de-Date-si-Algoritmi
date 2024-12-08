NAME = list
CC = gcc-14
CFLAGS = -fanalyzer -Wall -Wextra -Werror
SRC = $(wildcard *.c)
OBJ = $(wildcard *.o)
HEADER = $(NAME).h
EXPORT_OBJ = $(NAME).o
EXE = $(NAME).exe

all:
	clear
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)
	./$(EXE)

leaks: run
	leaks -q --atExit -- ./$(EXE)
