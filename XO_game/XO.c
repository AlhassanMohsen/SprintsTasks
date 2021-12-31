
#include "XO.h"

static u8_t gau8_Board[9]= {' ',' ',' ',' ',' ',' ',' ',' ',' '};

/********************************************//**
 * \brief this function is meant to print the game
 * board on the screen
 * \param takes no parameters
 * \return return void
 *
 ***********************************************/

void XO_PrintBoard(void)
{
    u8_t u8_BoardNavigator=0;
    for (u8_t u8_counter =0 ; u8_counter<3;u8_counter++)
    {
        printf("|%c|%c|%c|\n",gau8_Board[u8_BoardNavigator],gau8_Board[u8_BoardNavigator+1],gau8_Board[u8_BoardNavigator+2]);
        u8_BoardNavigator = ((u8_counter+1)*3);
    }


}


/********************************************//**
 * \brief this function is used to write a symbol
 in one of the Game Board fields

 * \param u8_SquareNum: is a u8 number that
 represent which field the user want to write on
 and it is a number between 1 and 9

 * \param u8_PlayerSymbol : is the Symbol that the
 user wants to write and it only can be X or O

 * \return this function return a u8_t number represent if the input is valid or not
 *
 ***********************************************/

u8_t XO_WriteToBoard(u8_t u8_SquareNum, u8_t u8_PlayerSymbol)
{
    u8_t u8_ErrorState = OK;

    /**< square code is used to map the inputs of the side keypad to the index of the game board */
    u8_t au8_SquareNumCode[9]={6,7,8,3,4,5,0,1,2};

    u8_SquareNum--;

    /**< perform check to make sure that the square number player entered is valid where it is only allowed to enter a square between 1-9 and must be an empty square */
    if (((u8_SquareNum<9) && (XO_u8CheckAvailability(au8_SquareNumCode[u8_SquareNum]))&& ((u8_PlayerSymbol=='X')||(u8_PlayerSymbol=='O'))))
    {
        /**< if all check passed write the player symbol to the chosen square */
        gau8_Board[au8_SquareNumCode[u8_SquareNum]]=u8_PlayerSymbol;
    }else{
        /**< if not change the return value to NOK to indicate an input violation */
        u8_ErrorState = NOK;
    }

    return u8_ErrorState;
}

/********************************************//**
 * \brief this function return the player move
 *
 * \param this takes no parameters
 * \return this function return a u16 integer that
 represent the move of the player this is a number between 1-9
 *
 ***********************************************/

u16_t XO_u8GetPlayerMove(void)
{
    u16_t u16_PlayerMove;
    scanf("%hu",&u16_PlayerMove);
    return u16_PlayerMove;
}

/********************************************//**
 * \brief this function return the state of the game
 which can be NO_WINNER, X_WIN or O_WIN.
 *
 * \param this function take no parameters
 * \return a u8 number represent the game state where
    0: NO_WINNER
    1: X_WIN
    2: O_WIN
 *
 ***********************************************/

u8_t XO_u8GameState(void)
{
    u8_t u8_GameState= NO_WINNER;

    /**< Check on the vertical squares to see if there is a three consecutive squares have the same symbol and if found declare the winner   */
    for (u8_t counter=0;counter<7;counter+=3)
    {
        if ((gau8_Board[counter]==gau8_Board[counter+1])&&(gau8_Board[counter]==gau8_Board[counter+2])&&gau8_Board[counter]!=' ')
        {
            if (gau8_Board[counter]=='X')
            {
                u8_GameState= X_WINNER;
                break;
            }
            else{
                u8_GameState= O_WINNER;
                break;
            }
        }
    }

    if (u8_GameState==NO_WINNER)
    {
        /**<if there is no winner in the vertical Check on the horizontal if found declare the winner   */
        for (u8_t counter=0;counter<3;counter++)
        {
           if ((gau8_Board[counter]==gau8_Board[counter+3])&&(gau8_Board[counter]==gau8_Board[counter+6])&&gau8_Board[counter]!=' ')
           {
               if (gau8_Board[counter]=='X')
               {
                   u8_GameState= X_WINNER;
                   break;
               }
               else{
                   u8_GameState= O_WINNER;
                   break;
               }
          }else{
                     //NOP
          }
       }
    }else{
               //NOP
    }

    if (u8_GameState==NO_WINNER)
    {
         /**<if there is no winner in the horizontal too Check on the diagonal axis if found declare the winner   */
        if ((gau8_Board[0]==gau8_Board[4])&&(gau8_Board[0]==gau8_Board[8])&&gau8_Board[0]!=' ')
        {
            if (gau8_Board[0]=='X')
            {
                u8_GameState= X_WINNER;

            }
            else{
                u8_GameState= O_WINNER;

            }

        }else if ((gau8_Board[2]==gau8_Board[4])&&(gau8_Board[2]==gau8_Board[6])&&gau8_Board[2]!=' ')
        {

            if (gau8_Board[2]=='X')
            {
                u8_GameState= X_WINNER;

            }
            else{
                u8_GameState= O_WINNER;

            }
        }else{
            //NOP
        }
    }else{
       //NOP
    }

    return u8_GameState;

}

/********************************************//**
 * \brief this function is used to check if the board fields are full yet
 *
 * \param takes no arguments

 * \return return 0 if the Board is not yet full and 1 if it is full
 *
 ***********************************************/

u8_t XO_IsBoardFull(void)
{
    u8_t u8_BoardState = BOARD_FULL;
    for (u8_t u8_counter=0;u8_counter<9;u8_counter++)
    {
        if (gau8_Board[u8_counter]==' ')
        {
            u8_BoardState=BOARD_EMPTY;
        }else{
            //NOP
        }
    }

    return u8_BoardState;
}

/********************************************//**
 * \brief This function is used to reset the field of the board to blank squares
 *
 * \param void
 * \return void
 *
 ***********************************************/

void XO_u8ResetBoard(void)
{
    for (u8_t u8_counter=0;u8_counter<9;u8_counter++)
    {
        gau8_Board[u8_counter]=' ';
    }
}

/********************************************//**
 * \brief This function is used to check if the given square is blank or not
 *
 * \param u8_SquareNum      u8_t number represent the square we want to check
 * \param
 * \return  u8_t number either SQUARE_AVAILABLE or SQUARE_NOT_AVAILABLE
 *
 ***********************************************/

u8_t XO_u8CheckAvailability(u8_t u8_SquareNum)
{
    u16_t u8_SquareState;
    if (gau8_Board[u8_SquareNum]==' ')
    {
        u8_SquareState= SQUARE_AVAILABLE;
    }else{
        u8_SquareState= SQUARE_NOT_AVAILABLE;
    }

    return u8_SquareState;
}
