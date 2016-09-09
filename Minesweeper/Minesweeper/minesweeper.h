/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			minesweeper.h
* Date Created:		1/12/16
* Modifications:	1/17/16
*
* Class: Minesweeper
*
* Purpose:
*	This class controls the flow of the Minesweeper game. It also
*	provides the interface to the Minesweeper game from the user's
*	perspective.
*
* Manager functions:
*	Minesweeper()
*		Creates a Minesweeper game with a board to hold the data and
*		the bool to signal the end of the game initialized to false.
*
*	Minesweeper(const Minesweeper & copy)
*
*	~Minesweeper()
*
*	Minesweeper & operator=(const Minesweeper & rhs)
*
* Methods:
*	void RunGame()
*		Provides the entrance into the game and exit out of the game.
*
*	void ChooseDifficulty()
*		Allows the user to choose the game difficulty.
*
*	void InterpretDifficultyChoice(int choice)
*		Creates board based on user's specified difficulty
*
*	void GameLoop()
*		Loops through the main portion of the game until the user
*		either quits, wins, or loses.
*
*	void ExplainBoardSymbols()
*		Displays a key of the symbols used on the board.
*
*	void ChooseAction()
*		Allows user to choose a move to make on the board.
*
*	void InterpretActionChoice(int choice)
*		Determines which action the user wants to do.
*
*	void UncoverCell()
*		Allows user to specify which cell to uncover.
*
*	void FlagCell()
*		Allows user to specify which cell to flag.
*
*	void RemoveFlaggedCell()
*		Allows user to specify which cell to remove a flag from.
**********************************************************************/

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "board.h"

class Minesweeper
{
	public:
		//Default Ctor
		Minesweeper();

		//Copy Ctor
		Minesweeper(const Minesweeper & copy);

		//Default Dtor
		~Minesweeper();

		//Assignment Operator
		Minesweeper & operator=(const Minesweeper & rhs);

		//Provides the entrance into the game and exit out of the game
		void RunGame();

	private:
		//Allows user to choose game difficulty
		void ChooseDifficulty();

		//Creates board based on user specified difficulty
		void InterpretDifficultyChoice(int choice);

		//Runs the game until the user quits, wins, or loses
		void GameLoop();

		//Displays key of the symbols used on the board
		void ExplainBoardSymbols();

		//Allows user to choose move to make on board
		void ChooseAction();

		//Determines which action the user wanted to do
		void InterpretActionChoice(int choice);

		//Allows user to specify which cell to uncover
		void UncoverCell();

		//Allows user to specify which cell to flag
		void FlagCell();

		//Allows user to specify which flag to remove
		void RemoveFlaggedCell();

		Board m_gameBoard;	//Actual board for game
		bool m_endGame;		//Flags when game is over
};

#endif //MINESWEEPER_H