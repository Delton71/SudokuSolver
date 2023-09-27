#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define SIZE 9

char** ReadSudoku();
void PrintSudoku(char** board);

void SolveSudoku(char** board);

void FreeSudoku(char** board);

#endif /* SUDOKUSOLVER_H */