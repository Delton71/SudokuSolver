CC=gcc
CFLAGS=-Wall
SOURCE=main.c sudokusolver.c
OUT=SudokuSolver

INPUT=input.txt
OUTPUT=output.txt

all: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(OUT)
	./$(OUT) < $(INPUT) > $(OUTPUT)

clean: $(OUT)
	rm -rf $(OUT)
