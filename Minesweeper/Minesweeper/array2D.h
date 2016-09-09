/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			array2D.h
* Date Created:		1/8/16
* Modifications:	1/12/16
*
* Class: Array2D
*
* Purpose:
*	This class creates a dynamic two-dimensional array, using a
*	one-dimensional array to store the two-dimensional array data in
*	row-major order.
*
* Manager functions:
*	Array2D()
*		Creates an Array2D with zero rows and columns initially.
*
*	Array2D(int row, int col)
*		Creates an Array2D with the number of rows and columns as
*		specified in the parameters.
*
*	Array2D(const Array2D<T> & copy)
*
*	~Array2D()
*
*	Array2D<T> & operator=(const Array2D<T> & rhs)
*
* Methods:
*	int getRow() const
*		Returns value of the number of rows.
*
*	int getColumn() const
*		Returns value of the number of columns.
*
*	void setRow(int row)
*		Sets value of the number of rows.
*
*	void setColumn(int col)
*		Sets value of the number of columns.
*
*	const Row<T> operator[](int rowDesired) const
*		Overloads the [] operator to specify a desired row index of the
*		Array2D, allowing a Row object to be returned in order to call
*		the overloaded [] operator in the Row object to specify a
*		desired column index of the Array2D.
*
*	T & Select(int rowDesired, int columnDesired) const
*		Select a desired element of the Array2D by taking a desired
*		row and column pair as parameters and converting to a valid
*		index of row-major order.
**********************************************************************/

#ifndef ARRAY2D_H
#define ARRAY2D_H

#include "array.h"

template <typename T>
class Row;

template <typename T>
class Array2D
{
public:
	//Default Ctor
	Array2D();

	//Overloaded 2-arg Ctor
	Array2D(int row, int col);	//Total # rows, Total # columns

	//Copy Ctor
	Array2D(const Array2D<T> & copy);

	//Default Dtor
	~Array2D();

	//Assignment Operator
	Array2D<T> & operator=(const Array2D<T> & rhs);

	//Getters for m_row and m_col
	int getRow() const;
	int getColumn() const;

	//Setter for m_row and m_col
	void setRow(int row);
	void setColumn(int col);

	//Overloaded [] Operator
	const Row<T> operator[](int rowDesired) const;

	//Selects array element from row-major order
	T & Select(int rowDesired, int columnDesired) const;

private:
	Array<T> m_array1D;		//1D array to store actual array data
	int m_row;		//Total # rows
	int m_col;		//Total # columns
};

/**********************************************************************
* Purpose:
*	To construct an instance of an Array2D and initialize the data
*	members to defaut values.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
template <typename T>
Array2D<T>::Array2D() : m_row(0), m_col(0)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of an Array2D and initialize the data
*	members to values of the parameters.
*
* Precondition:
*	Two intergers specifying the number of rows and columns for the
*	Array2D.
*
* Postcondition:
*	The data members are initialized to the values of the parameters,
*	if desired length is not negative.
**********************************************************************/
template <typename T>
Array2D<T>::Array2D(int row, int col) : m_row(row), m_col(col)
{
	//If either row or column is negative
	if (row < 0 || col < 0)
	{
		//Cannot have array of negative length
		m_row = 0;
		m_col = 0;
		throw Exception("ERROR: Cannot set row or column sizes to negative values.");
	}
	//Else if row or column is zero
	else if (row == 0 || col == 0)
	{
		//Make both row and column zero
		m_row = 0;
		m_col = 0;
	}

	//Set the length of the 1D array
	m_array1D.setLength(row * col);
}

/**********************************************************************
* Purpose:
*	To construct an instance of an Array2D with data members whose
*	initial values are copied from data members of an existing Array2D
*	object.
*
* Precondition:
*	An existing Array2D object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing Array2D object, unless the existing Array2D has
*	negative row or column values.
**********************************************************************/
template <typename T>
Array2D<T>::Array2D(const Array2D<T> & copy) : m_row(0), m_col(0)
{
	//If either row or column of existing Array2D is negative
	if (copy.m_row < 0 || copy.m_col < 0)
	{
		//Cannot have array of negative length
		throw Exception("ERROR: Cannot set row or column sizes to negative values.");
	}
	//Else if either row or column of existing Array2D is zero
	else if (copy.m_row == 0 || copy.m_col == 0)
	{
		//Use Array1D to set length to zero
		m_array1D.setLength(m_row * m_col);
	}
	else
		*this = copy;	//Use assignment operator
}

/**********************************************************************
* Purpose:
*	To reset the data members to default values, and destroy the
*	Array2D.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are re-initialized to default values.
**********************************************************************/
template <typename T>
Array2D<T>::~Array2D()
{
	m_col = 0;
	m_row = 0;
}

/**********************************************************************
* Purpose:
*	To assign one existing Array2D object to another existing Array2D
*	object by copying values of data members from one to another.
*
* Precondition:
*	An existing Array2D object passed by const ref.
*
* Postcondition:
*	One existing Array2D object is assigned to another existing Array2D
*	object.
**********************************************************************/
template <typename T>
Array2D<T> & Array2D<T>::operator=(const Array2D<T> & rhs)
{
	//If object addresses are not the same
	if (this != &rhs)
	{
		m_array1D = rhs.m_array1D;	//Use Array's assignment operator
		m_row = rhs.m_row;
		m_col = rhs.m_col;
	}

	return *this;
}

/**********************************************************************
* Purpose:
*	To retrieve the value of the number of rows.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The value of the number of rows is returned.
**********************************************************************/
template <typename T>
int Array2D<T>::getRow() const
{
	return m_row;
}

/**********************************************************************
* Purpose:
*	To retrieve the value of the number of columns.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The value of the number of columns is returned.
**********************************************************************/
template <typename T>
int Array2D<T>::getColumn() const
{
	return m_col;
}

/**********************************************************************
* Purpose:
*	To set the value of the number of rows to the parameter value only
*	if the parameter is non-negative.
*
* Precondition:
*	An integer representing the desired number of rows.
*
* Postcondition:
*	The value of the number of rows is set to the parameter value,
*	unless the parameter is negative.
**********************************************************************/
template <typename T>
void Array2D<T>::setRow(int row)
{
	//If number of rows is negative
	if (row < 0)
	{
		//Cannot have array of negative length
		m_row = 0;
		throw Exception("ERROR: Cannot set row size to negative value.");
	}
	//Else if number of rows is zero
	else if (row == 0)
	{
		//Make both row and column zero
		m_row = 0;
		m_col = 0;
	}

	m_row = row;
	m_array1D.setLength(m_row * m_col);		//Set the length of the 1D array
}

/**********************************************************************
* Purpose:
*	To set the value of the number of columns to the parameter value
*	only if the parameter is non-negative.
*
* Precondition:
*	An integer representing the desired number of columns.
*
* Postcondition:
*	The value of the number of columns is set to the parameter value,
*	unless the parameter is negative. The data of the array is
*	adjusted based on whether the number of columns is increasing or
*	decreasing.
**********************************************************************/
template <typename T>
void Array2D<T>::setColumn(int col)
{
	//If number of columns is negative
	if (col < 0)
	{
		//Cannot have array of negative length
		m_col = 0;
		throw Exception("ERROR: Cannot set column size to negative value.");
	}
	//Else if number of columns is zero
	else if (col == 0)
	{
		//Make both row and column zero
		m_row = 0;
		m_col = 0;
		m_array1D.setLength(m_row * m_col);		//Use Array1D to set length to zero
	}
	//Else adjust current data of array based on new column size
	else
	{
		Array<T> tempArray(m_row * col);	//Temp 1D array with new length

		//If increasing # of columns
		if (col > m_col)
		{
			int tempArrayCount = -1;		//Tracks element #s of larger tempArray
			int originalArrayCount = -1;	//Tracks element #s of smaller m_array1D

			//Iterate through each row
			for (int i = 0; i < m_row; i++)
			{
				//Iterate through each column of the original (smaller) array
				for (int j = 0; j < m_col; j++)
				{
					tempArrayCount++;		//Increment element counter for larger tempArray
					originalArrayCount++;	//Increment element counter for smaller m_array1D

					//Assign element of original array to correct new element location in the temp array
					tempArray[tempArrayCount] = m_array1D[originalArrayCount];
				}
				//Increment temp array element counter to start over at first column of next row
				tempArrayCount += (col - m_col);
			}
		}
		//Else reducing # of columns
		else
		{
			int tempArrayCount = -1;		//Tracks element #s of tempArray
			int originalArrayCount = -1;	//Tracks element #s of m_array1D

			//Iterate through each row
			for (int i = 0; i < m_row; i++)
			{
				//Iterate through each column of the temp (smaller) array
				for (int j = 0; j < col; j++)
				{
					tempArrayCount++;		//Increment element counter for smaller tempArray
					originalArrayCount++;	//Increment element counter for larger m_array1D

					//Assign element of original array to correct new element location in the temp array
					tempArray[tempArrayCount] = m_array1D[originalArrayCount];
				}
				//Increment original array element counter to start over at first column of next row
				originalArrayCount += (m_col - col);
			}
		}

		m_array1D = tempArray;
		m_col = col;
	}
}

/**********************************************************************
* Purpose:
*	To overload the [] operator to specify a desired row index of the
*	Array2D.
*
* Precondition:
*	An integer representing the desired row index.
*
* Postcondition:
*	If row index value is valid, a Row object is instantiated and
*	immediately returned, in order to use the Row object's overloaded
*	[] operator to specify a desired column index where the Row object
*	is returned.
**********************************************************************/
template<typename T>
const Row<T> Array2D<T>::operator[](int rowDesired) const
{
	//If accessing invalid row index value
	if (rowDesired < 0 || rowDesired >(m_row - 1))
		throw Exception("ERROR: Array row index is out of bounds.");

	//Instantiate and return Row object
	return Row<T>(*this, rowDesired);
}

/**********************************************************************
* Purpose:
*	To select the desired element of the Array2D by taking the desired
*	row and column pair and converting to a valid index of row-major
*	order.
*
* Precondition:
*	Two integers specifying the desired row and column element pair
*	to access in the Array2D.
*
* Postcondition:
*	An Array1D object at the desired element specified in row-major
*	order is returned.
**********************************************************************/
template<typename T>
T & Array2D<T>::Select(int rowDesired, int columnDesired) const
{
	//Store row and column pair as a row-major ordered index value
	int indexRowMajorOrder = (rowDesired * m_col) + columnDesired;

	//Return desired index of array
	return m_array1D[indexRowMajorOrder];
}

#endif //ARRAY2D_H