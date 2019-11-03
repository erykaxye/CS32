#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std; 

// h for history. This command shows you for each grid point how many times at that location a Flatulan was preached 
//to but was not converted: dot means 0, a letter character A through Y means 1 through 25 (A means 1, B means 2, etc.) 
//and Z means 26 or more.

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nCols; j++)
			grid[i][j] = '.';
}
//The constructor initializes a History object that corresponds to a City with nRows rows and nCols columns.You may assume
//(i.e., you do not have to check) that it will be called with a first argument that does not exceed MAXROWS and a second 
//that does not exceed MAXCOLS, and that neither argument will be less than 1.

bool History::record(int r, int c)
{
	if (r < 0 && r > m_rows  &&  c < 0 && c > m_cols)
		return false;

	char& gridChar = grid[r - 1][c - 1];
	switch (gridChar)
	{
	case '.':  gridChar = 'A'; break;
	case 'A':  gridChar = 'B'; break;
	case 'Z':  break;
	default:   gridChar++; break;
	}
	return true;
}
//The record function is to be called to notify the History object that a Flatulan was preached to but was not converted 
//at a grid point.The function returns false if row r, column c is not within the City; otherwise, it returns true after 
//recording what it needs to. This function expects its parameters to be expressed in the same coordinate system as the City
//(e.g., row 1, column 1 is the upper - left - most position). 

void History::display() const
{
	// Draw the grid

	int r, c;
	clearScreen();
	for (r = 0; r < m_rows; r++)
	{
		for (c = 0; c < m_cols; c++)
			cout << grid[r][c];
		cout << endl;
	}
	cout << endl;
}
//The display function clears the screen and displays the history grid as the posted programs do. This function does clear the screen, 
//display the history grid, and write an empty line after the history grid; it does not print the Press enter to continue.after the display. 

//	The class declaration(with any private members you choose to add to support your implementation) must be in a file named History.h, 
//and the implementation of the History class's member functions must be in History.cpp. If you wish, you may add a public destructor to 
//the History class. You must not add any other public members to the class. (This implies, for example, that you must not add a public 
//default constructor.) The only member function of the History class that may write to cout is History::display.

//This command shows you for each grid point how many times at that location a Flatulan was preached to but was not converted: 
//dot means 0, a letter character A through Y means 1 through 25 (A means 1, B means 2, etc.) and Z means 26 or more.