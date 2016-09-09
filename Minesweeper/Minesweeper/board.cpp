/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			board.cpp
* Date Created:		1/12/16
* Modifications:	1/17/16
**********************************************************************/

#include "board.h"

//Need for randomization
#include <cstdlib>
using std::srand;
#include <ctime>
using std::time;

//Need for colors
#include <Windows.h>

#include <iostream>
using std::cout;

/**********************************************************************
* Purpose:
*	To construct an instance of a Board and initialize the data member
*	containing the number of mines to a default value of zero.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data member containing number of mines is initialized to default
*	value of zero.
**********************************************************************/
Board::Board() : m_numMines(0)
{
	//Placed here b/c needs only run once
	srand((unsigned int)time(NULL));
}

/**********************************************************************
* Purpose:
*	To construct an instance of a Board with data members whose
*	values are copied from data members of an existing Board object.
*
* Precondition:
*	An existing Board object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing Board object.
**********************************************************************/
Board::Board(const Board & copy) : m_numMines(0)
{
	//Use assignment operator
	*this = copy;
}

/**********************************************************************
* Purpose:
*	To reset the data members to default values, and destroy the Board.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are reset to default values.
**********************************************************************/
Board::~Board()
{
	//Clear the array that creates the board
	ResetEmptyBoard();
	//Reset to default value
	m_numMines = 0;
}

/**********************************************************************
* Purpose:
*	To assign one existing Board object to another existing Board
*	object by copying values of data members from one to another.
*
* Precondition:
*	An existing Board object passed by const ref.
*
* Postcondition:
*	One existing Board object is assigned to another existing Board
*	object.
**********************************************************************/
Board & Board::operator=(const Board & rhs)
{
	if (this != &rhs)
	{
		//Use Array2D's assignment operator
		m_arrayCells = rhs.m_arrayCells;
		m_numMines = rhs.m_numMines;
	}

	return *this;
}

/**********************************************************************
* Purpose:
*	To create the Board with a specified number of rows, columns, and
*	mines.
*
* Precondition:
*	Three integers specifying the number of rows, columns, and mines
*	to apply to the Board.
*
* Postcondition:
*	A Board with the specified number of rows, columns, and mines is
*	created. A call to the ShuffleMines() method is made.
**********************************************************************/
void Board::CreateBoard(int row, int column, int numMines)
{
	//Set a board to a specified size
	m_arrayCells.setRow(row);
	m_arrayCells.setColumn(column);

	//Store total number of mines
	m_numMines = numMines;

	//Randomly assign mines to board
	ShuffleMines();
}

/**********************************************************************
* Purpose:
*	To allow the user to uncover a cell on the board, unless the
*	specified cell is already uncovered, has a flag, or is an invalid
*	element.
*
* Precondition:
*	Two integers specifying the row and column pair to uncover.
*
* Postcondition:
*	The specified cell is uncoverd only if it is a valid cell to
*	uncover.
**********************************************************************/
void Board::UncoverCell(int row, int column)
{
	try
	{
		//See if cell is in bounds (no exception thrown from Array2D)
		m_arrayCells[row][column];
	}
	catch (Exception & ex)
	{
		//Catch Array2D exception from accessing invalid elements
		//Throw new exception to inform the user & leave this method
		throw Exception("ERROR: That cell is not part of the board.");
	}

	//If cell is covered
	if (m_arrayCells[row][column].GetState() == COVERED)
	{
		//If cell has no adjacent mines
		if (m_arrayCells[row][column].GetValue() == NO_ADJ_MINES)
		{
			FloodFill(row, column);
		}
		else
		{
			//Uncover cell
			m_arrayCells[row][column].SetState(UNCOVERED);
		}
	}
	//Else cannot uncover cell
	else
		throw Exception("ERROR: Cannot uncover a cell that is already uncovered or flagged.");
}

/**********************************************************************
* Purpose:
*	To allow the user to add a flag to a cell on the board, unless
*	the specified cell already has a flag, is uncovered, or is an
*	invalid element.
*
* Precondition:
*	Two integers specifying the row and column pair to add the flag to.
*
* Postcondition:
*	A flag is added to the specified cell only if it is a valid cell
*	to add a flag to.
**********************************************************************/
void Board::FlagCell(int row, int column)
{
	try
	{
		//See if cell is in bounds (no exception thrown from Array2D)
		m_arrayCells[row][column];
	}
	catch (Exception & ex)
	{
		//Catch Array2D exception from accessing invalid elements
		//Throw new exception to inform the user & leave this method
		throw Exception("ERROR: That cell is not part of the board.");
	}

	//If cell is covered
	if (m_arrayCells[row][column].GetState() == COVERED)
	{
		//Flag cell
		m_arrayCells[row][column].SetState(FLAGGED);
	}
	//Else cannot flag cell
	else
		throw Exception("ERROR: Cannot flag a cell that is already uncovered or flagged.");
}

/**********************************************************************
* Purpose:
*	To allow the user to remove a flag from a cell on the board, unless
*	the specified cell does not have a flag or is an invalid element.
*
* Precondition:
*	Two integers specifying the row and column pair to remove the flag
*	from.
*
* Postcondition:
*	A flag is removed from the specified cell only if it is a valid
*	cell to remove a flag from.
**********************************************************************/
void Board::RemoveFlaggedCell(int row, int column)
{
	try
	{
		//See if cell is in bounds (no exception thrown from Array2D)
		m_arrayCells[row][column];
	}
	catch (Exception & ex)
	{
		//Catch Array2D exception from accessing invalid elements
		//Throw new exception to inform the user & leave this method
		throw Exception("ERROR: That cell is not part of the board.");
	}

	//If cell is flagged
	if (m_arrayCells[row][column].GetState() == FLAGGED)
	{
		//Remove flag and reset to covered
		m_arrayCells[row][column].SetState(COVERED);
	}
	//Else cannot unflag cell
	else
		throw Exception("ERROR: Cannot unflag a cell that is not already flagged.");
}

/**********************************************************************
* Purpose:
*	To determine whether a particular cell contains a mine.
*
* Precondition:
*	Two integers specifying a row and column pair.
*
* Postcondition:
*	A bool specifying whether the particular cell is a mine is
*	returned.
**********************************************************************/
bool Board::IsMine(int row, int column)
{
	bool isMine = false;	//Indicates if cell is a mine

	if (m_arrayCells[row][column].GetValue() == MINE)
		isMine = true;

	return isMine;
}

/**********************************************************************
* Purpose:
*	To uncover more cells upon uncovering a cell w/zero adjacent mines.
*	Every cell around a cell w/zero adjacent mines will be checked to
*	determine if it can be uncovered. 
*
* Precondition:
*	A cell w/zero adjacent mines was uncovered. Two integers specifying
*	the row and column pair that was uncovered is passed to the method.
*
* Postcondition:
*	The method will recursively call itself while more cells w/zero
*	adjacent mines are uncovered.
**********************************************************************/
void Board::FloodFill(int row, int column)
{
	//If cell is in bounds of board
	if (row != -1 && row != m_arrayCells.getRow() && column != -1 && column != m_arrayCells.getColumn())
	{
		//If cell is still covered
		if (m_arrayCells[row][column].GetState() == COVERED)
		{
			//If cell is not a mine
			if (m_arrayCells[row][column].GetValue() != MINE)
			{
				//Uncover cell
				m_arrayCells[row][column].SetState(UNCOVERED);

				//If cell has no adjacent mines
				if (m_arrayCells[row][column].GetValue() == NO_ADJ_MINES)
				{
					//Continue flood fill effect

					//Check North cell
					FloodFill(row - 1, column);
					//Check East cell
					FloodFill(row, column + 1);
					//Check South cell
					FloodFill(row + 1, column);
					//Check West cell
					FloodFill(row, column - 1);
				}
			}
		}
	}
}

/**********************************************************************
* Purpose:
*	To display the current state of the Board to the screen.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The current state of the Board is displayed to the screen.
**********************************************************************/
void Board::DisplayBoard()
{
	system("cls");

	//For each row on the board
	for (int i = 0; i < m_arrayCells.getRow(); i++)
	{
		//For each column on the board
		for (int j = 0; j < m_arrayCells.getColumn(); j++)
		{
			//If the cell is uncovered
			if (m_arrayCells[i][j].GetState() == UNCOVERED)
			{
				//Display symbol for a mine
				if (m_arrayCells[i][j].GetValue() == MINE)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 127);
					cout << "# ";
				}
				//Display symbol for no adjacent mines
				else if (m_arrayCells[i][j].GetValue() == NO_ADJ_MINES)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
					cout << "0 ";
				}
				//Display symbol for 1 adjacent mine
				else if (m_arrayCells[i][j].GetValue() == ONE_ADJ_MINE)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 114);
					cout << "1 ";
				}
				//Display symbol for 2 adjacent mine
				else if (m_arrayCells[i][j].GetValue() == TWO_ADJ_MINES)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 126);
					cout << "2 ";
				}
				//Display symbol for 3 adjacent mine
				else if (m_arrayCells[i][j].GetValue() == THREE_ADJ_MINES)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 124);
					cout << "3 ";
				}
				//Display symbol for 4 adjacent mine
				else if (m_arrayCells[i][j].GetValue() == FOUR_ADJ_MINES)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 115);
					cout << "4 ";
				}
				//Display symbol for 5 adjacent mine
				else if (m_arrayCells[i][j].GetValue() == FIVE_ADJ_MINES)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 117);
					cout << "5 ";
				}
				//Display symbol for 6 adjacent mine
				else if (m_arrayCells[i][j].GetValue() == SIX_ADJ_MINES)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 121);
					cout << "6 ";
				}
				//Display symbol for 7 adjacent mine
				else if (m_arrayCells[i][j].GetValue() == SEVEN_ADJ_MINES)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 113);
					cout << "7 ";
				}
				//Display symbol for 8 adjacent mine
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 123);
					cout << "8 ";
				}
			}
			//Else if the cell is flagged
			else if (m_arrayCells[i][j].GetState() == FLAGGED)
			{
				//Display symbol for flag
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
				cout << "! ";
			}
			//Else the cell is covered
			else
			{
				//Display "empty" covered spots
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 120);
				cout << "* ";
			}

			//Reset screen to default colors
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		//Move down a line on the screen
		cout << "\n";
	}
}

/**********************************************************************
* Purpose:
*	To determine whether the user has won the game by either uncovering
*	all cells that are not mines or by flagging all the mines (and no
*	others).
*
* Precondition:
*	<None>
*
* Postcondition:
*	A bool specifying whether the user won the game is returned.
**********************************************************************/
bool Board::WonGame()
{
	bool wonGame = true;
	int numFlags = 0;
	int numMinesFlagged = 0;

	//Check if all cells are uncovered (other than ones with mines)
	for (int i = 0; i < m_arrayCells.getRow(); i++)
	{
		for (int j = 0; j < m_arrayCells.getColumn(); j++)
		{
			//If a non-mine cell is still covered
			if (m_arrayCells[i][j].GetState() == COVERED && m_arrayCells[i][j].GetValue() != MINE)
				wonGame = false;

			//Else if a flagged cell is not a mine
			else if (m_arrayCells[i][j].GetState() == FLAGGED && m_arrayCells[i][j].GetValue() != MINE)
			{
				numFlags++;
				wonGame = false;
			}

			//If a flagged cell is a mine
			if (m_arrayCells[i][j].GetState() == FLAGGED && m_arrayCells[i][j].GetValue() == MINE)
			{
				numFlags++;
				numMinesFlagged++;
			}
		}
	}

	//If all mines are flagged (and no other cells are flagged)
	if (numFlags == m_numMines && numMinesFlagged == m_numMines)
		wonGame = true;

	return wonGame;
}

/**********************************************************************
* Purpose:
*	To reset the length of the array that contains the board data to
*	zero so that it will deallocate before a new game begins.
*
* Precondition:
*	The board has data.
*
* Postcondition:
*	The board has no size or data.
**********************************************************************/
void Board::ResetEmptyBoard()
{
	//Removes board data from array and resets length to zero
	m_arrayCells.setRow(0);
	m_arrayCells.setColumn(0);
}

/**********************************************************************
* Purpose:
*	To randomize the placement of the mines on the Board.
*
* Precondition:
*	The Board starts with no mines.
*
* Postcondition:
*	The mines are randomly assigned to different cells on the Board.
*	A call to the AssignCellValues() method is made.
**********************************************************************/
void Board::ShuffleMines()
{
	int countMines = 0;		//Condition for while loop counting # of
							//mines that have been assigned to board

	//Loop until all mines have been added
	while (countMines < m_numMines)
	{
		//Randomly choose a row and column to indicate a random cell
		int cellRow = (rand() % (m_arrayCells.getRow()));
		int cellCol = (rand() % (m_arrayCells.getColumn()));

		//If randomly chosen cell does not contain a mine
		if (m_arrayCells[cellRow][cellCol].GetValue() != MINE)
		{
			//Set value of cell to contain a mine
			m_arrayCells[cellRow][cellCol].SetValue(MINE);
			countMines++;
		}
	}

	//Fill leftover cells with values for # of adjacent mines
	AssignCellValues();
}

/**********************************************************************
* Purpose:
*	To increment the number of adjacent mines in each cell surrounding
*	each cell with a mine.
*
* Precondition:
*	All non-mine cells start at zero adjacent cells.
*
* Postcondition:
*	Each cell has a number specifying the number of adjacent mines to
*	that particular cell.
**********************************************************************/
void Board::AssignCellValues()
{
	//Iterate through each row
	for (int i = 0; i < m_arrayCells.getRow(); i++)
	{
		//Iterate through each column
		for (int j = 0; j < m_arrayCells.getColumn(); j++)
		{
			//If cell contains a mine
			if (m_arrayCells[i][j].GetValue() == MINE)
			{
				//Increment surrounding cells' # adjacent mines
				//if not out of bounds & not containing a mine

				//North cell
				if ((i - 1) != -1 && m_arrayCells[i - 1][j].GetValue() != MINE)
					m_arrayCells[i - 1][j].SetValue(static_cast<Value>(static_cast<int>(m_arrayCells[i - 1][j].GetValue()) + 1));

				//NorthEast cell
				if ((i - 1) != -1 && (j + 1) != m_arrayCells.getColumn() && m_arrayCells[i - 1][j + 1].GetValue() != MINE)
				{
					m_arrayCells[i - 1][j + 1].SetValue(static_cast<Value>(static_cast<int>(m_arrayCells[i - 1][j + 1].GetValue()) + 1));
				}

				//East cell
				if ((j + 1) != m_arrayCells.getColumn() && m_arrayCells[i][j + 1].GetValue() != MINE)
				{
					m_arrayCells[i][j + 1].SetValue(static_cast<Value>(static_cast<int>(m_arrayCells[i][j + 1].GetValue()) + 1));
				}

				//SouthEast cell
				if ((i + 1) != m_arrayCells.getRow() && (j + 1) != m_arrayCells.getColumn() && m_arrayCells[i + 1][j + 1].GetValue() != MINE)
				{
					m_arrayCells[i + 1][j + 1].SetValue(static_cast<Value>(static_cast<int>(m_arrayCells[i + 1][j + 1].GetValue()) + 1));
				}

				//South cell
				if ((i + 1) != m_arrayCells.getRow() && m_arrayCells[i + 1][j].GetValue() != MINE)
				{
					m_arrayCells[i + 1][j].SetValue(static_cast<Value>(static_cast<int>(m_arrayCells[i + 1][j].GetValue()) + 1));
				}

				//SouthWest cell
				if ((i + 1) != m_arrayCells.getRow() && (j - 1) != -1 && m_arrayCells[i + 1][j - 1].GetValue() != MINE)
				{
					m_arrayCells[i + 1][j - 1].SetValue(static_cast<Value>(static_cast<int>(m_arrayCells[i + 1][j - 1].GetValue()) + 1));
				}

				//West cell
				if ((j - 1) != -1 && m_arrayCells[i][j - 1].GetValue() != MINE)
				{
					m_arrayCells[i][j - 1].SetValue(static_cast<Value>(static_cast<int>(m_arrayCells[i][j - 1].GetValue()) + 1));
				}

				//NorthWest cell
				if ((i - 1) != -1 && (j - 1) != -1 && m_arrayCells[i - 1][j - 1].GetValue() != MINE)
				{
					m_arrayCells[i - 1][j - 1].SetValue(static_cast<Value>(static_cast<int>(m_arrayCells[i - 1][j - 1].GetValue()) + 1));
				}
			}
		}
	}
}
