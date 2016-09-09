/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			minesweeper.cpp
* Date Created:		1/12/16
* Modifications:	1/17/16
**********************************************************************/

#include "minesweeper.h"

#include <iostream>
using std::cout;
using std::cin;

/**********************************************************************
* Purpose:
*	To construct an instance of a Minesweeper game and initialize the
*	data member specifying the end of the game to the default value of
*	false.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data member specifying the end of the game is initialized to
*	default value of false.
**********************************************************************/
Minesweeper::Minesweeper() : m_endGame(false)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of a Minesweeper game with data members
*	whose values are copied from data members of an existing
*	Minesweeper object.
*
* Precondition:
*	An existing Minesweeper object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing Minesweeper object.
**********************************************************************/
Minesweeper::Minesweeper(const Minesweeper & copy) : m_endGame(false)
{
	*this = copy;	//Use assignment operator
}

/**********************************************************************
* Purpose:
*	To reset the data members to default values, and destroy the
*	Minesweeper object.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are reset to default values.
**********************************************************************/
Minesweeper::~Minesweeper()
{
	//Reset to default value
	m_endGame = false;
}

/**********************************************************************
* Purpose:
*	To assign one existing Minesweeper object to another existing
*	Minesweeper object by copying values of data members from one to
*	another.
*
* Precondition:
*	An existing Minesweeper object passed by const ref.
*
* Postcondition:
*	One existing Minesweeper object is assigned to another existing
*	Minesweeper object.
**********************************************************************/
Minesweeper & Minesweeper::operator=(const Minesweeper & rhs)
{
	if (this != &rhs)
	{
		//Use Board's assignment operator
		m_gameBoard = rhs.m_gameBoard;
		m_endGame = rhs.m_endGame;
	}

	return *this;
}

/**********************************************************************
* Purpose:
*	To provide an entry point into the game and exit out of the game.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The welcome message is displayed, the ChooseDifficulty() method
*	is called, and the program closes if the user chooses not to play
*	again upon ending the previous game.
**********************************************************************/
void Minesweeper::RunGame()
{
	char playAgain = '\0';	//Contains user's choice whether to play again

	do
	{
		//Upon starting the game
		system("cls");

		cout << "\t\tWelcome to Minesweeper!\n\n";
		cout << "Objective: Uncover all the cells that don't contain mines,\n"
			<< "or flag all (and only) the cells that do contain mines.\n";
		cout << "Game is lost if: A cell is uncovered that contains a mine.\n";
		cout << "Warning: It is possible to lose on the first try to uncover a cell.\n\n";

		ChooseDifficulty();

		//Upon finishing the game
		cout << "\nDo you want to play again? (y/n): ";
		cin >> playAgain;
	}
	while (playAgain == 'y');

	cout << "\nThanks for playing!\n\n";
}

/**********************************************************************
* Purpose:
*	To allow the user to choose the difficulty of the game.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The user chooses a difficulty level, and the
*	InterpretDifficultyChoice() method is called and passed the user's
*	difficulty choice.
**********************************************************************/
void Minesweeper::ChooseDifficulty()
{
	int choice = 0;		//Contains user menu choice for game difficulty

	cout << "Please select the difficulty level:\n"
		<< "1) Beginner\n"
		<< "2) Intermediate\n"
		<< "3) Expert\n\n";
	cout << "Your choice: ";
	cin >> choice;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (choice < 1 || choice > 3)
	{
		cout << "\nChoice must be a number between 1 and 3. Please try again: ";
		cin >> choice;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	InterpretDifficultyChoice(choice);
}

/**********************************************************************
* Purpose:
*	To create the appropriate sized game board based on the user's
*	specified difficulty choice.
*
* Precondition:
*	An integer specifying the user's difficulty choice.
*
* Postcondition:
*	An appropriately sized game board is created and the GameLoop()
*	method is called.
**********************************************************************/
void Minesweeper::InterpretDifficultyChoice(int choice)
{
	//Create appropriately sized game board
	switch (choice)
	{
	case 1:
		m_gameBoard.CreateBoard(SMALL_SIZE, SMALL_SIZE, BEGINNER_MINES);
		break;
	case 2:
		m_gameBoard.CreateBoard(MEDIUM_SIZE, MEDIUM_SIZE, INTERMEDIATE_MINES);
		break;
	case 3:
		m_gameBoard.CreateBoard(MEDIUM_SIZE, LARGE_SIZE, EXPERT_MINES);
		break;
	}

	//Run main game loop
	GameLoop();
}

/**********************************************************************
* Purpose:
*	To run the main portion of the game until the user either quits,
*	wins, or loses
*
* Precondition:
*	The board is the appropriate size with appropriate data.
*
* Postcondition:
*	The game ends when the user quits, wins, or loses. The game board
*	is reset to its default empty state, and the flag to end the game
*	is reset to false in case the user plays again.
**********************************************************************/
void Minesweeper::GameLoop()
{
	//Display initial game board and key symbols on board
	m_gameBoard.DisplayBoard();
	ExplainBoardSymbols();

	//Stay in loop until user quits, wins, or looses
	while (m_endGame != true)
	{
		ChooseAction();
	}

	//Reset state of game to initial values
	m_gameBoard.ResetEmptyBoard();
	m_endGame = false;
}

/**********************************************************************
* Purpose:
*	To display a key of symbols used on the game board.
*
* Precondition:
*	The game board is usually displayed first.
*
* Postcondition:
*	The key of symbols used on the game board is displayed.
**********************************************************************/
void Minesweeper::ExplainBoardSymbols()
{
	cout << "Covered = * , Flagged = ! , Mine = # , "
		 << "Number of adjacent mines = <Numbers>";
}

/**********************************************************************
* Purpose:
*	To allow the user to choose whether to uncover a cell, flag a cell,
*	remove a flag from a cell, or quit the current game.
*
* Precondition:
*	Called throughout the course of the game from the GameLoop() method.
*
* Postcondition:
*	The user chooses an action to take, and the InterpretActionChoice()
*	method is called and passed the user's action choice.
**********************************************************************/
void Minesweeper::ChooseAction()
{
	int choice = 0;		//Contains user menu choice for board action

	cout << "\n\nPlease select an action:\n"
		<< "1) Uncover a cell\n"
		<< "2) Flag a cell\n"
		<< "3) Remove a flag\n"
		<< "4) Quit this game\n";
	cout << "Your choice: ";
	cin >> choice;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (choice < 1 || choice > 4)
	{
		cout << "\nChoice must be a number between 1 and 4. Please try again: ";
		cin >> choice;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	InterpretActionChoice(choice);
}

/**********************************************************************
* Purpose:
*	To call the appropriate method, or set the flag to end the game,
*	based on the user's choice of action.
*
* Precondition:
*	An integer specifying the user's action choice.
*
* Postcondition:
*	The appropriate method is called or the flag to end the game is
*	set based on the user's choice of actions.
**********************************************************************/
void Minesweeper::InterpretActionChoice(int choice)
{
	//Choose appropriate choice of action
	switch (choice)
	{
	case 1:
		UncoverCell();
		break;
	case 2:
		FlagCell();
		break;
	case 3:
		RemoveFlaggedCell();
		break;
	case 4:
		m_endGame = true;
		break;
	}
}

/**********************************************************************
* Purpose:
*	To allow the user to specify which cell to uncover, if the cell is
*	a valid cell to uncover.
*
* Precondition:
*	User chooses to uncover a cell.
*
* Postcondition:
*	The user specified cell is uncovered if possible, the board is
*	re-displayed, the uncovered cell is checked to see if it contains
*	a mine, and a check to see if the user won the game occurs.
**********************************************************************/
void Minesweeper::UncoverCell()
{
	//-1 protects uncovering unwanted cell if a char gets stored into int
	int row = -1;	//User specified row coordinate
	int col = -1;	//User specified column coordinate

	//Display current game board and key symbols on board
	m_gameBoard.DisplayBoard();
	ExplainBoardSymbols();

	//Prompt for cell to uncover
	cout << "\n\nPlease enter coordinates of cell to uncover.\n";
	cout << "Row coordinate: ";
	cin >> row;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	cout << "Column coordinate: ";
	cin >> col;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	try
	{
		//Uncover cell and re-display board
		m_gameBoard.UncoverCell(row, col);
		m_gameBoard.DisplayBoard();
		ExplainBoardSymbols();

		//Check if cell contains a mine
		if (m_gameBoard.IsMine(row, col) == true)
		{
			m_endGame = true;
			cout << "\n\nThat cell contained a mine. Game over.\n\n";
		}
	}
	catch (Exception & ex)
	{	
		//Re-display board and display exception
		m_gameBoard.DisplayBoard();
		ExplainBoardSymbols();
		cout << "\n\n" << ex;
	}

	//Check if user won game
	if (m_gameBoard.WonGame() == true)
	{
		m_endGame = true;
		cout << "\n\nYou won!\n\n";
	}
}

/**********************************************************************
* Purpose:
*	To allow the user to specify which cell to flag, if the cell is
*	a valid cell to flag.
*
* Precondition:
*	User chooses to flag a cell.
*
* Postcondition:
*	The user specified cell is flagged if possible, the board is
*	re-displayed, and a check to see if the user won the game occurs.
**********************************************************************/
void Minesweeper::FlagCell()
{
	//-1 protects flagging unwanted cell if a char gets stored into int
	int row = -1;	//User specified row coordinate
	int col = -1;	//User specified column coordinate

	//Display current game board and key symbols on board
	m_gameBoard.DisplayBoard();
	ExplainBoardSymbols();

	//Prompt for cell to flag
	cout << "\n\nPlease enter coordinates of cell to flag.\n";
	cout << "Row coordinate: ";
	cin >> row;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	cout << "Column coordinate: ";
	cin >> col;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	try
	{
		//Flag cell and re-display board
		m_gameBoard.FlagCell(row, col);
		m_gameBoard.DisplayBoard();
		ExplainBoardSymbols();
	}
	catch (Exception & ex)
	{
		//Re-display board and display exception
		m_gameBoard.DisplayBoard();
		ExplainBoardSymbols();
		cout << "\n\n" << ex;
	}

	//Check if user won game
	if (m_gameBoard.WonGame() == true)
	{
		m_endGame = true;
		cout << "\n\nYou won!\n\n";
	}
}

/**********************************************************************
* Purpose:
*	To allow the user to specify which cell to remove a flag from, if
*	the cell is a valid cell to remove a flag from.
*
* Precondition:
*	User chooses to remove a flag from a cell.
*
* Postcondition:
*	The user specified cell is removed of its flag if possible, the
*	board is re-displayed, and a check to see if the user won the game
*	occurs.
**********************************************************************/
void Minesweeper::RemoveFlaggedCell()
{
	//-1 protects removing flag from unwanted cell if a char gets stored into int
	int row = -1;	//User specified row coordinate
	int col = -1;	//User specified column coordinate

	//Display current game board and key symbols on board
	m_gameBoard.DisplayBoard();
	ExplainBoardSymbols();

	//Prompt for cell to remove flag from
	cout << "\n\nPlease enter coordinates of cell to remove flag.\n";
	cout << "Row coordinate: ";
	cin >> row;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	cout << "Column coordinate: ";
	cin >> col;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	try
	{
		//Flag cell and re-display board
		m_gameBoard.RemoveFlaggedCell(row, col);
		m_gameBoard.DisplayBoard();
		ExplainBoardSymbols();
	}
	catch (Exception & ex)
	{
		//Re-display board and display exception
		m_gameBoard.DisplayBoard();
		ExplainBoardSymbols();
		cout << "\n\n" << ex;
	}

	//Check if user won game
	if (m_gameBoard.WonGame() == true)
	{
		m_endGame = true;
		cout << "\n\nYou won!\n\n";
	}
}