/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			stub.cpp
* Date Created:		1/12/16
* Modifications:	1/17/16
*
* Lab/Assignment: Lab 1 – Minesweeper
* 
* Overview:
*	This program simulates the classic Minesweeper game. There are
*	three levels: Beginner, Intermediate, and Expert. A board is
*	populated with a certain number of mines over a certain number
*	of cells based on the level. The rest of the cells are populated
*	with numbers representing how many mines are adjacent to a
*	particular cell. All cells start covered, and the user can either
*	uncover a cell, flag a cell to mark as a potential mine, or remove
*	a flag. If the user uncovers a cell with a mine, the user loses.
*	If the user uncovers all cells that are not mines, the user wins.
*	If the user has every mine flagged, and no other cells are flagged,
*	the user wins.
*
* Input:
*	The input will come from the keyboard. The user will enter numbers
*	to choose between menu items, and will also enter numbers to choose
*	an ordered row & column pair when specifying a certain cell to
*	apply an action to.
*
* Output:
*	The output will be displayed to the screen. Instructions for the
*	user, error messages to the user, and a the game board will be
*	displayed to the screen. 
**********************************************************************/

#include "minesweeper.h"

#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Minesweeper minesweeperGame;	//Create a Minesweeper game
	minesweeperGame.RunGame();		//Start the Minesweeper game

	return 0;
}