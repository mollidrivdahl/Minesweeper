/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			cell.cpp
* Date Created:		1/12/16
* Modifications:	1/17/16
**********************************************************************/

#include "cell.h"

/**********************************************************************
* Purpose:
*	To construct an instance of a Cell and initialize the data members
*	to default values.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
Cell::Cell() : m_state(COVERED), m_value(NO_ADJ_MINES)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of a Cell with data members whose initial
*	values are copied from data members of an existing Cell object.
*
* Precondition:
*	An existing Cell object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing Cell object.
**********************************************************************/
Cell::Cell(const Cell & copy) : m_state(COVERED), m_value(NO_ADJ_MINES)
{
	*this = copy;	//Use assignment operator
}

/**********************************************************************
* Purpose:
*	To reset the data members to default values, and destroy the Cell.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are reset to default values.
**********************************************************************/
Cell::~Cell()
{
	//Reset data members to default values
	m_state = COVERED;
	m_value = NO_ADJ_MINES;
}

/**********************************************************************
* Purpose:
*	To assign one existing Cell object to another existing Cell object
*	by copying values of data members from one to another.
*
* Precondition:
*	An existing Cell object passed by const ref.
*
* Postcondition:
*	One existing Cell object is assigned to another existing Cell
*	object.
**********************************************************************/
Cell & Cell::operator=(const Cell & rhs)
{
	if (this != &rhs)
	{
		//Assign rhs data members to lhs data members
		m_state = rhs.m_state;
		m_value = rhs.m_value;
	}
	
	return *this;
}

/**********************************************************************
* Purpose:
*	To set the state of the Cell.
*
* Precondition:
*	A State enum specifying the desired state of the Cell.
*
* Postcondition:
*	The state of the Cell is set to the parameter value.
**********************************************************************/
void Cell::SetState(State setter)
{
	m_state = setter;
}

/**********************************************************************
* Purpose:
*	To set the value of the Cell.
*
* Precondition:
*	A Value enum specifying the desired value of the Cell.
*
* Postcondition:
*	The value of the Cell is set to the parameter value.
**********************************************************************/
void Cell::SetValue(Value setter)
{
	m_value = setter;
}

/**********************************************************************
* Purpose:
*	To retrieve the state of the Cell.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The state of the Cell is returned.
**********************************************************************/
State Cell::GetState() const
{
	return m_state;
}

/**********************************************************************
* Purpose:
*	To retrieve the value of the Cell.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The value of the Cell is returned.
**********************************************************************/
Value Cell::GetValue() const
{
	return m_value;
}