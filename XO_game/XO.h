#ifndef XO_H_INCLUDED
#define XO_H_INCLUDED
#include <stdio.h>

#include "compiler.h"

#define NO_WINNER   0
#define X_WINNER    1
#define O_WINNER    2

#define BOARD_FULL  1
#define BOARD_EMPTY 0

#define SQUARE_AVAILABLE        1
#define SQUARE_NOT_AVAILABLE    0



void XO_PrintBoard(void);
u8_t XO_WriteToBoard(u8_t u8_SquareNum, u8_t u8_PlayerSymbol);
u8_t XO_IsBoardFull(void);
void XO_u8ResetBoard(void);
u8_t XO_u8CheckAvailability(u8_t u8_SquareNum);


#endif // XO_H_INCLUDED
