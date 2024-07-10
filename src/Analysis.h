#pragma once

#include "Data.cpp"
#include <unordered_map>
#include <set>

struct Analysis {
	/**
	 * Default constructor for the Analysis struct.
	 *
	 * An instance of this struct is used to carry out most of the computation in the main
	 * function.
	 */
	Analysis();

	/**
	 * Initializes the vector of Grids defined below as matrices_. Assigns a matrix to 
	 * every language and places frequency data into a 2D vector found in the Grid class.
	 */
	void _initializeMatrices();

	/**
	 * Finds the average word-length of every langauge among the top 10% of the 
	 * most frequently used words in the language.
	 *
	 * Stores the findings in the frequent_word_length vector.
	 */
	void averageFrequentWordLength();

	/**
	 * Finds the average word-length of every langauge among the entire list of frequently 
	 * used words in the language.
	 *
	 * Stores the findings in the word_length vector.
	 */
	void averageWordLength();

	/**
	 * Finds the most common color in every language.
	 *
	 * Stores the findings in the common_colors and common_colors_ranks vectors.
	 */
	void mostCommonColor();

	/**
	 * Simplifies the complicated vectors of the mostCommonColor() function and places the 
	 * results inside two 1-dimensional vectors, color_results and color_indices.
	 */
	void _simplify();

	/**
	 * Finds how similar every language is to every other language, and then places the 
	 * results into the hash table similarity.
	 */
	void findSimilarity();

	/**
	 * Finds how similar every language is to every other language, by comparing the 3% of words
	 * in the frequency data set for any equalities. The algorithm then moves on to the next 3%,
	 * and recursively continues until it reaches the 870th index.
	 * 
	 * @param  languageOne A matrix of the first language
	 * @param  languageTwo A matrix of the second language
	 * 
	 * @return             A similarity score comparing the two languages.
	 */
	unsigned similarityScore(Grid<std::string> & languageOne, Grid<std::string> languageTwo);

	/**
	 * Recursive helper function for the similarityScore() function.
	 * 
	 * @param  languageOne A vector containing data belonging to the first language
	 * @param  languageTwo A vector containing data belonging to the second language
	 * @param  index       The index at which to check for similarities for the next
	 *                     3%.
	 *                     
	 * @return             A similarity score.
	 */
	unsigned similaritySum(std::vector<std::string> & languageOne, std::vector<std::string> & languageTwo, 
		unsigned index);

	/**
	 * Creates a LanguageData vector similar to the languages one containing only
	 * english or english-translated languages.
	 */
	void createEnglishData();

	/**
	 * Assigns the values of the english_indices to the file_names of the .txt files
	 * in the hash table path_languages.
	 */
	void initializeHashTable();

	/**
	 * Cleans the numerical data that represents the distribution of the most common words
	 * in the english language. Specifically removes the words and keeps the integers in the 
	 * loaded data.
	 * 	
	 * @param data The distribution of frequency from the .txt file
	 */
	void cleanNumericalData(std::vector<std::string> & data);

	/**
	 * Writes a .txt file of any set of data to be visualized later on.
	 * @param name The name of the .txt file
	 * @param data The vector of data to be written
	 */
	template <typename T>
	void writeFile(std::string name, std::vector<T> & data);

	/**
	 * The following data structures are used to load in and store the data. 
	 *
	 * The matrices_ vector stored a 2D matrix for every language, while the languages and 
	 * english_languages vectors store a 900-length list of the frequency data. The 
	 * english_frequency vector stores the distribution of the most frequent words in the
	 * english language.
	 *
	 * The english_languages vector is a subset of the languages vector.
	 */
	std::vector<Grid<std::string>> matrices_;
	std::vector<LanguageData> languages;
	std::vector<LanguageData> english_languages;
	std::vector<std::string> english_frequency;

	/**
	 * The following data structures are used to create a bijection from the english
	 * indices and the names of the languages, and then from the names to a vector 
	 * storing how similar each language is to every other language.
	 */
	std::unordered_map<unsigned, std::string> path_languages;
	std::unordered_map<std::string, std::vector<unsigned>> similarity;

	/**
	 * The following data structures are used to perform the word length analysis on the 
	 * frequency language data sets. 
	 *
	 * The frequent_word_length vector stores the average length of the top 10% of 
	 * the frequency data. The word_length vector stores the average length of all
	 * the frequency data for each language.
	 */
	std::vector<double> frequent_word_length;
	std::vector<double> word_length;

	/**
	 * The following data structures are used to perform the color analysis on the 
	 * frequency language data sets. 
	 * 
	 * The common_colors vector stores a vector of strings that represents every language's 
	 * most common color. The common_colors_ranks vector stores a vector of unsigned indices 
	 * of where in the frequency list the common colors appeared.
	 *
	 * The color results vector stores every language's most common colors. The color indices
	 * vector stores the indices of where every language's most common colors occurred.
	 */
	std::vector<std::vector<std::string>> common_colors;
	std::vector<std::vector<unsigned>> common_colors_ranks;
	std::vector<std::string> color_results;
	std::vector<unsigned> color_indices;

	/**
	 * The elements in this vector represent the names of the .txt files where the
	 * frequency data is stored.
	 *
	 * This vector is traversed in order to load in the data. 
	 */
	const std::vector<std::string> file_names = {"english", "spanish only", "french only", "dutch only", "german_only", 
						"catalan only", "italian only", "turkish only", "esperanto only", "spanish_e", 
						"french_e", "dutch_e", "german_e", "catalan_e", "italian_e", "turkish_e", "esperanto_e"};

	/**
	 * These indices represent all the english or the english-translated languages
	 * from the paths vector above.
	 *
	 * 0 -> english
	 * 9 -> spanish_e (spanish translated to english)
	 * 10 -> french_e (french translated to english)
	 * ... et cetera.
	 */
	const std::vector<unsigned> english_indices = {0, 9, 10, 11, 12, 13, 14, 15, 16};

	/**
	 * These colors represent all the possible combinations of colors that can be
	 * found in the language data sets. This vector is repeatedly checked against
	 * to see if a language has this particular color.
	 */
	const std::vector<std::string> colors = {"black", "white", "green", "blue", "gold", "orange", "pink", "brown", "gray"};

	const unsigned kDimension = 30;
};