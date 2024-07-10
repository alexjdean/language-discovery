#include "Grid.h"

template <typename T>
Grid<T>::Grid() {/** Nothing here **/}

template <typename T>
Grid<T>::Grid(const unsigned & rows, const unsigned & columns, std::vector<T> & elements) 
 : rows_(rows), columns_(columns), elements_(elements) {
 	_initializeMatrix(rows, columns, elements);
}

template <typename T>
Grid<T>::Grid(const Grid & other) {
	rows_ = other.rows_;
	columns_ = other.columns_;
	elements_ = other.elements_;
	matrix = other.matrix;
}

template <typename T>
Grid<T>::~Grid() {/** Nothing to see here **/}

template <typename T>
void Grid<T>::_initializeMatrix(const unsigned & rows, const unsigned & columns, 
								std::vector<T> & elements) {
	std::queue<T> elements_copy;
 	matrix.resize(rows);

 	for(unsigned i = 0; i < elements.size(); i++) {
 		elements_copy.push(elements[i]);
 	}

 	for(unsigned i = 0; i < rows; i++) {
 		for(unsigned j = 0; j < columns; j++) {
 			matrix[i].push_back(elements_copy.front());
 			elements_copy.pop();
 		}
 	}
}

template <typename T>
Grid<T> & Grid<T>::operator=(const Grid<T> & other) {
	rows_ = other.rows_;
	columns_ = other.columns_;
	elements_ = other.elements_;

	return *this;
}

template <typename T>
unsigned Grid<T>::numRows() const {
	return rows_;
}

template <typename T>
void Grid<T>::setRows(unsigned rows) {
	rows_ = rows;
}

template <typename T>
unsigned Grid<T>::numColumns() const {
	return columns_;
}

template <typename T>
void Grid<T>::setColumns(unsigned columns) {
	columns_ = columns;
}

template <typename T>
std::vector<T> Grid<T>::getElementsVector() const {
	return elements_;
}

template <typename T>
void Grid<T>::setElementsVector(std::vector<T> elements) {
	elements_ = elements;
}

template <typename T>
unsigned Grid<T>::gridSize() const {
	unsigned size = 0;

	for(unsigned i = 0; i < matrix.size(); i++) {
		size += matrix[i].size();
	}

	return size;
}

template <typename T>
bool Grid<T>::sameRowValue(unsigned index, T element) {
	std::basic_string<bool> same_element;

	for(unsigned i = 0; i < columns_; i++) {
		if(matrix[index][i] == element) {
			same_element.push_back(true);
		}
	}

	return same_element.length() == rows_;
}

template <typename T>
bool Grid<T>::sameColumnValue(unsigned index, T element) {
	std::basic_string<bool> same_element;

	for(unsigned i = 0; i < rows_; i++) {
		if(matrix[i][index] == element) {
			same_element.push_back(true);
		}
	}

	return same_element.length() == columns_;
}

template <typename T>
bool Grid<T>::sameDiagonalValue(T element, bool left_side) {
	std::basic_string<bool> same_element_left;
	std::basic_string<bool> same_element_right;

	for(unsigned i = 0; i < rows_; i++) {
		for(unsigned j = 0; j < columns_; j++) {
			if(i == j && matrix[i][j] == element) {
				same_element_left.push_back(true);
			}
			
			if(i == j && reverseRow(matrix)[i][j] == element) {
				same_element_right.push_back(true);
			}
		}
	}

	if(left_side) {
		return same_element_left.length() == rows_;
	}

	return same_element_right.length() == rows_;
}

template<typename T>
bool Grid<T>::existsRowElement(unsigned index, T element) {
	for(unsigned i = 0; i < rows_; i++) {
		if(matrix[index][i] == element) {
			return true;
		}
	}

	return false;
}

template<typename T>
bool Grid<T>::existsColumnElement(unsigned index, T element) {
	for(unsigned i = 0; i < columns_; i++) {
		if(matrix[i][index] == element) {
			return true;
		}
	}

	return false;
}

template<typename T>
bool Grid<T>::existsBoxElement(unsigned row_index, unsigned column_index, T element) {
	for(unsigned i = 0; i < rows_ / sqrt(rows_); i++) {
		for(unsigned j = 0; j < columns_ / sqrt(columns_); j++) {
			if(matrix[i + row_index][j + column_index] == element) {
				return true;
			}
		}
	}

	return false;
}

template <typename T>
bool Grid<T>::isVacant() {
	const char VACANT_SPACE = '_';
	std::basic_string<bool> elements;

	for(unsigned i = 0; i < rows_; i++) {
		for(unsigned j = 0; j < columns_; j++) {
			if(matrix[i][j] == VACANT_SPACE) {
				elements.push_back(true);
			}
		}
	}

	return elements.length() == rows_ * columns_;
}

template <typename T>
bool Grid<T>::existsVacant() {
	const char VACANT_SPACE = '_';

	for(unsigned i = 0; i < rows_; i++) {
		for(unsigned j = 0; j < columns_; j++) {
			if(matrix[i][j] == VACANT_SPACE) {
				return true;
			}
		}
	}

	return false;
}

template <typename T>
bool Grid<T>::validNum(unsigned row_index, unsigned column_index, char num) {
	bool repeated_row = !existsRowElement(row_index, num);
	bool repeated_column = !existsColumnElement(column_index, num);

	bool repeated_box_element = !existsBoxElement(row_index - 
		row_index % (unsigned) sqrt(rows_), column_index - 
		column_index % (unsigned) sqrt(columns_), num);

	return repeated_row && repeated_column && repeated_box_element;
}

template <typename T>
std::vector<std::vector<T>> Grid<T>::getMatrix() const {
	return matrix;
}

template <typename T>
std::vector<std::vector<char>> Grid<T>::reverseRow(std::vector<std::vector<char>> matrix) {
	for(unsigned i = 0; i < rows_; i++) {
		std::reverse(matrix[i].begin(), matrix[i].end());
	}

	return matrix;
}