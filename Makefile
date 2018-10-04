CC = gcc
DB = gdb

IDIR = ./include
CFLAGS = -I$(IDIR) -lm -std=c11 `sdl2-config --cflags --libs`

BIN = ./bin
DATA = ./data

SRCS = ./src/*.c 
MAIN = main.c
OUT = Modos-Normais.out

all: 
	$(CC) $(SRCS) $(MAIN) -o $(BIN)/$(OUT) $(CFLAGS)

run:
	$(BIN)/$(OUT) 50 -10 0 0

debug:
	$(CC) -g $(SRCS) $(MAIN) -o $(BIN)/$(OUT) $(CFLAGS)

clean:
	rm $(BIN)/*

