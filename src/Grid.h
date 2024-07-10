#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

#include <string>
#include <vector>
#include <queue>

template<typename T>
class Grid {
	public:
		/**
		 * The default constructor for the Grid class
		 */
		Grid();

		/**
		 * Constructor that takes in a templated vector of elements and places it
		 * inside the matrix
		 * 
		 * @param rows     The number of rows
		 * @param columns  The number of columns
		 * @param elements A templated vector of elements to be placed in the
		 *                 matrix
		 */
		Grid(const unsigned & rows, const unsigned & columns, std::vector<T> & elements);

		/**
		 * Copy constructor for a Grid object
		 *
		 * @param other Another object of type Grid
		 */
		Grid(const Grid & other);

		/**
		 * Destructor for the Grid class
		 */
		~Grid();

		/**
		 * Helper function for the constructor
		 * 
		 * Initializes the 2D vector that serves as the matrix for the Grid class
		 * 
		 * @param rows     The number of rows
		 * @param columns  The number of columns
		 * @param elements A templated vector of elements to be placed in the
		 *                 matrix
		 */
		void _initializeMatrix(const unsigned & rows, const unsigned & columns, 
								std::vector<T> & elements);
		
		/**
		 * An overloaded = operator which assigns a Grid object to be equal to another
		 *
		 * @param other Another object of type Grid
		 */
		Grid & operator=(const Grid & other);

		/**
		 * An overloaded << operator which prints the contents of the 2D vector to console
		 *
		 * @param stream A standard string ostream used to output strings
		 * @param grid   A const object of type Grid
		 */
		friend std::ostream & operator<<(std::ostream & stream, const Grid & grid) {
			for(auto const & vec : grid.getMatrix()) {
				for(auto const & num : vec) {
					stream << num << " ";
				}

				stream << std::endl;
			}

			return stream;
		}

		/**
		 * An overloaded >> operator which takes user-input and assigns values to the 2D vector
		 *
		 * @param in     A standard string istream used to take in strings
		 * @param grid   An object of type Grid
		 */
		friend std::istream & operator>>(std::istream & in, Grid & grid) {
			in >> grid.board_ >> grid.rows_ >> grid.columns_;
			grid._initializeMatrix(grid.rows_, grid.columns_, grid.board_);
			return in;
		}

		/**
		 * Finds the total number of rows in the grid
		 * 
		 * @return The number of rows
		 */
		unsigned numRows() const;

		/**
		 * Assigns an integer value to the rows variable
		 * 
		 * @param rows The value to be assigned
		 */
		void setRows(unsigned rows);
	
		/**
		 * Finds the total number of columns in the grid
		 * 
		 * @return The number of columns
		 */
		unsigned numColumns() const;

		/**
		 * Assigns an integer value to the columns variable
		 * 
		 * @param columns The value to be assigned
		 */
		void setColumns(unsigned columns);

		/**
		 * Gets the vector of elements used to initialize the matrix
		 *
		 * @return The vector of elements
		 */
		std::vector<T> getElementsVector() const;

		/**
		 * Sets the vector of elements 
		 * 
		 * @param elements The inputted vector to be used
		 */
		void setElementsVector(std::vector<T> elements);

		/**
		 * Finds the total size of the grid, found such that the size always equals rows * columns
		 * 
		 * @return The total size of the grid
		 */
		unsigned gridSize() const;
		
		/**
		 * Checks if the inputted element is the same for an entire row at an inputted index
		 * 
		 * @param  index   The index of a column
		 * @param  element Any given element in the grid
		 * 
		 * @return         True if the element is present at every point along the row, 
		 *                 false otherwise
		 */
		bool sameRowValue(unsigned index, T element);
		
		/**
		 * Checks if the inputted element is the same for an entire column at an inputted index
		 * 
		 * @param  index   The index of a row
		 * @param  element Any given element in the grid
		 * 
		 * @return         True if the element is present at every point along the column, 
		 *                 false otherwise
		 */
		bool sameColumnValue(unsigned index, T element);
	
		
		/**
		 * Checks if the inputted element is the same for the diagonal at a specified side
		 * 
		 * @param  element   Any given element in the grid
		 * @param  left_side The side of the grid that the top diagonal starts on
		 * 
		 * @return           True if the element is present along a grid diagonal, false otherwise
		 */
		bool sameDiagonalValue(T element, bool left_side);

		/**
		 * Checks if the inputted element is found in the row
		 * 
		 * @param  index   The index of a row
		 * @param  element Any given element in the grid
		 * 
		 * @return         True if the element is present at every point along the column, 
		 *                 false otherwise
		 */
		bool existsRowElement(unsigned index, T element);

		/**
		 * Checks if the inputted element is found in the column
		 * 
		 * @param  index   The index of a row
		 * @param  element Any given element in the grid
		 * 
		 * @return         True if the element is present at every point along the column, 
		 *                 false otherwise
		 */
		bool existsColumnElement(unsigned index, T element);

		/**
		 * Checks if the inputted element is found in box subset of the grid
		 * 
		 * @param  row_index      The index of a row
		 * @param  column_index   The index of a column
		 * @param  element        Any given element in the grid
		 * 
		 * @return                True if the element is present in the box subset, false otherwise
		 */
		bool existsBoxElement(unsigned row_index, unsigned column_index, T element);
	
		/**
		 * Checks if the grid is vacant (devoid of unique elements)
		 * 
		 * @return True if the grid is vacant, false otherwise
		 */
		bool isVacant();

		/**
		 * Checks if there exists a vacant spot on the grid
		 * 
		 * @return True if the spot exists, false otherwise
		 */
		bool existsVacant();

		/**
		 * Checks to see if a number can be assigned to the partitioned box matrix, assuming the value
		 * has not been assigned yet
		 * 		
		 * @param  row_index    An index to a row
		 * @param  column_index An index to a column
		 * @param  num          The number to be assigned
		 * 
		 * @return              True if the number can be assigned, false otherwise
		 */
		bool validNum(unsigned row_index, unsigned column_index, char num);
	
		/**
		 * Provides access to the 2D vector that represents the grid
		 * 
		 * @return A 2D vector representing the grid
		 */
		std::vector<std::vector<T>> getMatrix() const;
	
		/**
		 * Reverses all of the rows of a given grid
		 * 
		 * @return A 2D vector with all of its rows reversed
		 */
		std::vector<std::vector<char>> reverseRow(std::vector<std::vector<char>> grid);
	
	private:
		unsigned rows_;
		unsigned columns_;
		std::vector<T> elements_;
	
		/**
		 * A 2D vector under the hood that serves as a 2 dimensional grid
		 */
		std::vector<std::vector<T>> matrix;
};