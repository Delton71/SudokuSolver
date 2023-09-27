#include "sudokusolver.h"

// #define SUDOKU_DEBUG

int row[SIZE];
int col[SIZE];
int box[SIZE];

int SudokuDFS(char** board);
int IsCellNumValid(char c, int i, int j);
void FreeN(char** arr, int n);
void PrintBits(int size, void *ptr);


char** ReadSudoku() {
  char** board = (char**) malloc(SIZE * sizeof(char *));
  if (!board) {
    return NULL;
  }

  char c = '\0';
  for (int i = 0; i < SIZE; ++i) {
    board[i] = (char *) malloc(SIZE);
    if (!board[i]) {
      FreeN(board, i);
      return NULL;
    }
    for (int j = 0; j < SIZE; ++j) {
      scanf("%c", &board[i][j]);
    }
    scanf("%c", &c);
  }

  return board;
}

void PrintSudoku(char** board) {
  if (!board) {
    return;
  }
  
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      printf("%c", board[i][j]);
    }
    puts("");
  }
}

void SolveSudoku(char** board) {
  if (!board) {
    return;
  }
  memset(row, 0, sizeof(row));
  memset(col, 0, sizeof(col));
  memset(box, 0, sizeof(box));

  int cell_num = 0;
  int ind = 0;
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (board[i][j] != '.') {
        cell_num = board[i][j] - '1';
        ind = (1 << cell_num);

        row[i] |= ind;
        col[j] |= ind;
        box[(i / 3) * 3 + (j / 3)] |= ind;
      }
    }
  }

  #ifdef SUDOKU_DEBUG
    for (int i = 0; i < SIZE; ++i) {
      printf("I = %d\n", i);
      PrintBits(sizeof(row[i]), &row[i]);
      PrintBits(sizeof(col[i]), &col[i]);
      PrintBits(sizeof(box[i]), &box[i]);
      puts("");
    }
  #endif

  SudokuDFS(board);
}

int IsCellNumValid(char c, int i, int j) {
  int ind = (1 << (c - '1'));
  if ((row[i] & ind) || (col[j] & ind) || (box[(i / 3) * 3 + (j / 3)] & ind)) {
    return 0;
  }
  return 1;
}

int SudokuDFS(char** board) {
  int ind = 0;

  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (board[i][j] == '.') {
        ind = 1;
        for (char c = '1'; c <= '9'; ++c, ind <<= 1) {
          if (IsCellNumValid(c, i, j)) {
            board[i][j] = c;
            row[i] |= ind;
            col[j] |= ind;
            box[(i / 3) * 3 + (j / 3)] |= ind;

            if (SudokuDFS(board)) {
              return 1;
            }

            row[i] ^= ind;
            col[j] ^= ind;
            box[(i / 3) * 3 + (j / 3)] ^= ind;
            board[i][j] = '.';
          }
        }
        return 0;
      }
    }
  }

  return 1;
}

void FreeSudoku(char** board) {
  FreeN(board, SIZE);
}

void FreeN(char** board, int n) {
  if (!board) {
    return;
  }
  for (int i = 0; i < n; ++i) {
    if (board[i]) {
      free(board[i]);
    }
  }
  if (board) {
    free(board);
  }
}

void PrintBits(int size, void *ptr) {
  unsigned char *b = (unsigned char *) ptr;
  unsigned char byte = 0;
  
  for (int i = size - 1; i >= 0; i--) {
    for (int j = 7; j >= 0; j--) {
      byte = (b[i] >> j) & 1;
      printf("%u", byte);
    }
    printf(" ");
  }
  printf("\n");
}
