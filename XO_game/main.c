#include <stdio.h>

#include "XO.h"


int main()
{
    u16_t u16_mainPlayerInput;
    u8_t u8_PlayerTurn=0;
    u8_t u8_RetGameState=NO_WINNER;
    u8_t u8_RetBoardState=BOARD_EMPTY;

    /**< Print the main menu of the Game */

    printf("\t \t Welcome To XO Game\n");
    printf("\t \t Please use your keyboard side number pad as the game board\n");
    printf("|7|8|9|\n");
    printf("|4|5|6|\n");
    printf("|1|2|3|\n");

    printf("\t \t Press 1 To continue to Game and 0 to Exit\n");
    scanf("%uh",&u16_mainPlayerInput);

    while (1)
    {

        u8_RetGameState=NO_WINNER;
        u8_RetBoardState=BOARD_EMPTY;

        /**< reset the board and Empty it at every new game */
        XO_u8ResetBoard();

        /**< if the player chose to play a new game start the sequence of the game */
    if (u16_mainPlayerInput==1)
    {
        system("cls");
        XO_PrintBoard();

        /**< While there is the game is not done yet */
        while (u8_RetGameState==NO_WINNER && u8_RetBoardState== BOARD_EMPTY)
        {
            /**< decide the player who has to play now */
           if (u8_PlayerTurn==0)
           {
               /**< Get the move from the player and loop until he enter a valid move then write this move to the board*/
               do{
                u16_mainPlayerInput=XO_u8GetPlayerMove();
                u8_PlayerTurn=1;
               }while(!XO_WriteToBoard(u16_mainPlayerInput,'X'));

           }else{

                /**< Get the move from the player and loop until he enter a valid move then write this move to the board*/
               do{
                u16_mainPlayerInput=XO_u8GetPlayerMove();
                u8_PlayerTurn=0;
               }while(!XO_WriteToBoard(u16_mainPlayerInput,'O'));

           }
           system("cls");
           XO_PrintBoard();

           /**< check if there a winner after this move or the board is full with no winner */
           u8_RetGameState=XO_u8GameState();
           u8_RetBoardState=XO_IsBoardFull();
        }

        /**< when game is ended go check the state variable to see who wins and display it on the screen */
        if (u8_RetGameState==X_WINNER)
        {
            system("cls");
            printf("Congratulation X You win this time.\n");
        }else if(u8_RetGameState==O_WINNER)
        {
            system("cls");
            printf("Congratulation O You win this time.\n");
        }else{
            system("cls");
            printf("Unfortunately,NO one win this one.\n");
        }

        printf("To play Again Press 1 To Exit Press 0");
        scanf("%uh",&u16_mainPlayerInput);
    }else {

        /**< Break from While(1) if the player chose not to play again */
        break;
    }
    }

    return 0;
}
