#include <stdio.h>
#include <stdlib.h>
#include "sudokusolver.h"

int main(int argc, char* argv[]) {
  char** board = ReadSudoku();
  SolveSudoku(board);
  PrintSudoku(board);
  FreeSudoku(board);
  return 0;
}
