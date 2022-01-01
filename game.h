#define R_MAX 3
#define C_MAX 3

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

void play(int *playerscore, int *computerscore, int *key, int *note);
void computer_play(char board[R_MAX][C_MAX], int R, int C);

void printboard(char board[R_MAX][C_MAX], int R, int C);
void clear(char board[R_MAX][C_MAX], int R, int C);
void putintoboard(char board[R_MAX][C_MAX], char ch, int x, int y);

char Win(char board[R_MAX][C_MAX], int R, int C);
int Fulled(char board[R_MAX][C_MAX], int R, int C);

void search(char board[R_MAX][C_MAX], int R, int C, int *X, int *Y, char ch, char ch2);

void printrule();
void totalmenu();
void menu();

void free_data(int *key, int *note, int *playerscore, int *computerscore);

