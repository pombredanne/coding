#ifndef __H__MYHEADER
#define __H__MYHEADER

#include<stdint.h>
#include<stdio.h>
#include<stdbool.h>

#define SIZE 4

extern uint32_t score;
extern uint32_t scheme;

//printf for test
void printfBoard(uint8_t board[SIZE][SIZE]);

//Paint 
void getColor(uint8_t value,char *color,size_t length); //这个函数没有修改！

void drawBoard(uint8_t board[SIZE][SIZE]);

void addRandom(uint8_t board[SIZE][SIZE]);

void initBoard(uint8_t board[SIZE][SIZE]);

//move or merge
void rotateBoard(uint8_t board[SIZE][SIZE]);

uint8_t findTarget(uint8_t array[SIZE],uint8_t x,uint8_t stop);

bool findPairDown(uint8_t board[SIZE][SIZE]);

bool slideArray(uint8_t array[SIZE]);

bool moveUp(uint8_t board[SIZE][SIZE]);

bool moveLeft(uint8_t board[SIZE][SIZE]);

bool moveRight(uint8_t board[SIZE][SIZE]);

bool moveDown(uint8_t board[SIZE][SIZE]);


//设置终端
void setBufferedInput(bool enable);

void signal_callback_handler(int signum);



uint8_t countEmpty(uint8_t board[SIZE][SIZE]);


bool gameEnded(uint8_t board[SIZE][SIZE]);

//Check functions

bool gameWin(void);

bool checkBoard(uint8_t board[SIZE][SIZE]);

int main_check(char *key,uint8_t board[SIZE][SIZE],uint8_t keyLen);

int paintFlag(char key[],uint8_t keyLen);

//Module special input

int getStr(char *buffer,int maxLen);

void str2hex(char *source,char *dest,int keyLen);


//Matrix Module  矩阵运算

//矩阵  转置
int getTransposeMatrix(uint8_t * matrix,uint8_t row,uint8_t column,uint8_t ** transposeMatrix);

int getTransposeMatrix_oneArray(uint8_t * matrix,uint8_t row,uint8_t column,uint8_t * transposeMatrix);

//C = A*B   要求：A的列数 = B的行数  ==> C的行数 = A的行数；C的列数 = B的列数
void matrixMul(uint8_t **A, uint8_t **B, uint32_t **C, uint8_t rowA, uint8_t columnB, uint8_t columnA);

void matrixMul_oneArray(uint8_t *A, uint8_t *B, uint32_t *C, uint8_t rowA, uint8_t columnB, uint8_t columnA);

#endif