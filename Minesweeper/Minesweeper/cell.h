/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			cell.h
* Date Created:		1/12/16
* Modifications:	1/17/16
*
* Class: Cell
*
* Purpose:
*	This class symbolizes the cells on a Minesweeper game board. It
*	manages the state and value of any given cell on the board.
*
* Manager functions:
*	Cell()
*		Creates a Cell with initial state set to covered and initial
*		value set to no adjacent mines.
*
*	Cell(const Cell & copy)
*
*	~Cell()
*
*	Cell & operator=(const Cell & rhs)
*
* Methods:
*	void SetState(State setter)
*		Sets the state of the Cell to one of the State enum values
*		specified as the parameter.
*
*	void SetValue(Value setter)
*		Sets the value of the Cell to one of the Value enum values
*		specified as the parameter.
*
*	State GetState() const
*		Returns the state of the Cell as one of the State enum values.
*
*	Value GetValue() const
*		Returns the value of the Cell as one of the Value enum values.
**********************************************************************/

#ifndef CELL_H
#define CELL_H

//Cell can have any of these states
enum State
{
	COVERED,
	UNCOVERED,
	FLAGGED
};

//Cell can be any of these values
enum Value
{
	NO_ADJ_MINES,
	ONE_ADJ_MINE,
	TWO_ADJ_MINES,
	THREE_ADJ_MINES,
	FOUR_ADJ_MINES,
	FIVE_ADJ_MINES,
	SIX_ADJ_MINES,
	SEVEN_ADJ_MINES,
	EIGHT_ADJ_MINES,
	MINE
};

class Cell
{
	public:
		//Default Ctor
		Cell();

		//Copy Ctor
		Cell(const Cell & copy);
		
		//Default Dtor
		~Cell();

		//Assignment Operator
		Cell & operator=(const Cell & rhs);

		//Setter for m_state and m_value
		void SetState(State setter);
		void SetValue(Value setter);

		//Getters for m_state and m_value
		State GetState() const;
		Value GetValue() const;

	private:
		State m_state;	//Stores Cell state
		Value m_value;	//Stores Cell value
};

#endif //CELL_H