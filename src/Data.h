#pragma once

#include <fstream>
#include "Grid.cpp"

struct LanguageData {
	/**
	 * Default constructor for the LanguageData struct
	 */
	LanguageData();

	/**
	 * Reads a file from the parameter path
	 * 
	 * @param filePath The path of the file
	 */
	void readFileIn(std::string filePath);

	/**
	 * Helper function for the readFileIn() function, adds the contents of the file being read in 
	 * to a vector that stores its data
	 * 	
	 * @param file The file being read in
	 * @param line An empty string
	 * @param data  The vector that stores the contents
	 */
	void _addContents(std::ifstream & file, std::string & line, std::vector<std::string> & data);

	/**
	 * Removes white space from the strings found in the data vector and changes every string
	 * to lowercase.
	 *
	 * @param data The vector containing the contents of the files read in
	 */
	void _removeWhiteSpace(std::vector<std::string> & data);

	std::vector<std::string> data_;
};