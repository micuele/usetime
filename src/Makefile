CC = gcc
CFLAGS = -Wall -Werror
LIBS = -lncurses

SRC_DIR = ../src
INC_DIR = ../src

SRC = $(SRC_DIR)/chart.c
INC = $(INC_DIR)/chart.h

OBJ = chart.o main.o
EXEC = test

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

chart.o: $(SRC) $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
