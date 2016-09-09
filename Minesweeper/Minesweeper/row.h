/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			row.h
* Date Created:		1/8/16
* Modifications:	1/12/16
*
* Class: Row
*
* Purpose:
*	This class creates a Row object to simulate a row element of a
*	two-dimensional array. Its main purpose is to overload the []
*	operator to access a column element of a two-dimensional array.
*
* Manager functions:
*	Row(const Array2D<T> & array2D, int rowDesired)
*		Creates a Row with data member values assigned to the values
*		of the parameters.
*
*	Row(const Row<T> & copy)
*
*	~Row();
*		
* Methods:
*	int getRowDesired() const;
*		Returns value of the row to access.
*
*	void setRowDesired(int rowDesired)
*		Sets value of the row to access.
*
*	T & operator[](int columnDesired) const
*		Overloads the [] operator to specify a desired column index of
*		the 2D array, and sends both desired row and column indices to
*		the Select method of Array2D to return the row-major ordered
*		index of the desired element.
**********************************************************************/

#ifndef ROW_H
#define ROW_H

#include "array2D.h"

template <typename T>
class Row
{
public:
	//2-arg Ctor
	Row(const Array2D<T> & array2D, int rowDesired);

	//Copy Ctor
	Row(const Row<T> & copy);

	//Default Dtor
	~Row();

	//Getter for m_rowDesired
	int getRowDesired() const;

	//Setter for m_rowDesired
	void setRowDesired(int rowDesired);

	//Overloaded [] Operator
	T & operator[](int columnDesired) const;

private:
	const Array2D<T> & m_array2D;	//2D Array
	int m_rowDesired;	//Row index to access
};

/**********************************************************************
* Purpose:
*	To construct an instance of a Row and initialize the data members
*	to the values of the parameters.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to the parameter values.
**********************************************************************/
template<typename T>
Row<T>::Row(const Array2D<T> & array2D, int rowDesired) : m_array2D(array2D), m_rowDesired(rowDesired)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of a Row with data members whose initial
*	values are copied from data members of an existing Row object.
*
* Precondition:
*	An existing Row object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing Row object.
**********************************************************************/
template<typename T>
Row<T>::Row(const Row<T> & copy) : m_array2D(copy.m_array2D), m_rowDesired(copy.m_rowDesired)
{}

/**********************************************************************
* Purpose:
*	To reset the data members to default values, and destroy the Row.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are reset to default values.
**********************************************************************/
template<typename T>
Row<T>::~Row()
{
	//Reset to default value
	m_rowDesired = 0;
}

/**********************************************************************
* Purpose:
*	To overload the [] operator to specify a desired column index of
*	the 2D array, and send both desired row and column indices to
*	the Select method of Array2D to return the row-major ordered index
*	of the desired element.
*
* Precondition:
*	An integer representing the desired column index.
*
* Postcondition:
*	If column index value is valid, the actual 2D array element from
*	the row-major order format is returned.
**********************************************************************/
template<typename T>
T & Row<T>::operator[](int columnDesired) const
{
	// If accessing invalid column index value
	if (columnDesired < 0 || columnDesired >(m_array2D.getColumn() - 1))
		throw Exception("ERROR: Array column index is out of bounds.");

	//Return actual 2D array element from the row-major order format
	return m_array2D.Select(m_rowDesired, columnDesired);
}

/**********************************************************************
* Purpose:
*	To retrieve the value of the desired row.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The value of the desired row is returned.
**********************************************************************/
template<typename T>
int Row<T>::getRowDesired() const
{
	return m_rowDesired;
}

/**********************************************************************
* Purpose:
*	To set the value of the desired row.
*
* Precondition:
*	An integer specifying the desired row element.
*
* Postcondition:
*	The value of the desired row is set to the parameter value.
**********************************************************************/
template<typename T>
void Row<T>::setRowDesired(int rowDesired)
{
	m_rowDesired = rowDesired;
}

#endif //ROW_H