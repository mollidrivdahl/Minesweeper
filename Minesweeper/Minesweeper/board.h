/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			board.h
* Date Created:		1/12/16
* Modifications:	1/17/16
*
* Class: Board
*
* Purpose:
*	This class symbolizes the board of Minesweeper game. It manages
*	all the changes to the Array2D of Cells that contains all the data
*	on the board.
*
* Manager functions:
*	Board()
*		Creates a Board with an Array2D of Cells and the number of
*		mines initialized to zero.
*
*	Board(const Board & copy)
*
*	~Board()
*
*	Board & operator=(const Board & rhs)
*
* Methods:
*	void CreateBoard(int row, int column, int numMines)
*		Creates a board w/specified number of rows, columns, and mines
*		as given by the parameters.
*
*	void UncoverCell(int row, int column)
*		Marks the cell given by the row and column pair as uncovered.
*
*	void FlagCell(int row, int column)
*		Marks the cell given by the row and column pair as flagged.
*
*	void RemoveFlaggedCell(int row, int column)
*		Removes a flag from the cell given by the row and column pair.
*
*	bool IsMine(int row, int column)
*		Checks if the cell given by the row and column pair contains
*		a mine.
*
*	void DisplayBoard()
*		Displays the board data as its current state in the game.
*
*	bool WonGame()
*		Checks if the user has won the game.
*
*	void ResetEmptyBoard()
*		Removes the rows and columns from the board so that it can be
*		removed of the data.
*
*	void ShuffleMines()
*		Randomizes the placement of the mines in the cells on the
*		board.
*
*	void AssignCellValues()
*		Increments the value for the number of adjacent mines for each
*		cell around any given cell with a mine.
*
*	void FloodFill(int row, int column)
*		Uncovers more cells upon uncovering the cell given by the row
*		and column pair if the cell has zero adjacent mines.
**********************************************************************/

#ifndef BOARD_H
#define BOARD_H

#include "row.h"
#include "cell.h"

//Row & column size for beginner level
const int SMALL_SIZE = 10;
//Row & column size for intermediate level, Row size for expert level
const int MEDIUM_SIZE = 16;
//Column size for expert level
const int LARGE_SIZE = 30;
//# mines for beginner level
const int BEGINNER_MINES = 10;
//# mines for intermediate level
const int INTERMEDIATE_MINES = 40;
//# mines for expert level
const int EXPERT_MINES = 100;

class Board
{	
	public:
		//Default Ctor
		Board();

		//Copy Ctor
		Board(const Board & copy);

		//Default Dtor
		~Board();

		//Assignment Operator
		Board & operator=(const Board & rhs);

		//Create board w/specified size & # of mines
		void CreateBoard(int row, int column, int numMines);

		//Mark a cell as uncovered
		void UncoverCell(int row, int column);

		//Mark a cell as flagged
		void FlagCell(int row, int column);

		//Remove a flag from a cell
		void RemoveFlaggedCell(int row, int column);

		//Check if a cell contains a mine
		bool IsMine(int row, int column);

		//Display current state of the board
		void DisplayBoard();

		//Check if user won the game
		bool WonGame();

		//Give board zero rows and columns to remove data
		void ResetEmptyBoard();
		
	private:
		//Places mines in random cells on board
		void ShuffleMines();

		//Increment cell values around each mine
		void AssignCellValues();

		//Uncover more cells upon uncovering a cell w/zero adjacent mines
		void FloodFill(int row, int column);

		Array2D<Cell> m_arrayCells;		//2D array of Cells holding board data
		int m_numMines;		//Contains total number of mines on board
};

#endif //BOARD_H