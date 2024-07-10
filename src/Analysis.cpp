#include "Analysis.h"

Analysis::Analysis() {
	_initializeMatrices();
}

void Analysis::_initializeMatrices() {
	for(unsigned i = 0; i < file_names.size(); i++) {
		LanguageData lang;
		languages.push_back(lang);
		languages[i].readFileIn("../data/" + file_names[i] + ".txt");
		Grid<std::string> matrix(kDimension, kDimension, languages[i].data_);
		matrices_.push_back(matrix);
	}

	LanguageData numerical;
	numerical.readFileIn("../data/english_numerical.txt");
	english_frequency = numerical.data_;
}

void Analysis::averageFrequentWordLength() {
	double count = 0;

	for(unsigned i = 0; i < matrices_.size(); i++) {
		for(unsigned j = 0; j < kDimension / 10; j++) {
			for(unsigned k = 0; k < kDimension; k++) {
				count += matrices_[i].getMatrix()[j][k].length();
			}
		}

		double frequency = count / (kDimension * kDimension / 10);
		frequent_word_length.push_back(frequency);
		count = 0;
	}
}

void Analysis::averageWordLength() {
	double count = 0;

	for(unsigned i = 0; i < matrices_.size(); i++) {
		for(unsigned j = 0; j < kDimension; j++) {
			for(unsigned k = 0; k < kDimension; k++) {
				count += matrices_[i].getMatrix()[j][k].length();
			}
		}

		double frequency = count / (kDimension * kDimension);
		word_length.push_back(frequency);
		count = 0;
	}
}

void Analysis::mostCommonColor() {
	for(unsigned i = 0; i < matrices_.size(); i++) {
		std::vector<std::string> lang_colors;
		std::vector<unsigned> lang_colors_ranks;

		for(unsigned j = 0; j < kDimension; j++) {
			for(unsigned k = 0; k < kDimension; k++) {
				for(unsigned l = 0; l < colors.size(); l++) {
					if(matrices_[i].getMatrix()[j][k] == colors[l]) {
						lang_colors.push_back(colors[l]);

						for(unsigned m = 0; m < languages[i].data_.size(); m++) {
							if(colors[l] == languages[i].data_[m]) {
								lang_colors_ranks.push_back(m);
							}
						}
					}
				}
			}
		}

		common_colors.push_back(lang_colors);
		common_colors_ranks.push_back(lang_colors_ranks);
	}

	_simplify();
}

void Analysis::_simplify() {
	for(const auto & colors : common_colors) {
		for(const auto & c : colors) {
			color_results.push_back(c);
		}
	}

	for(const auto & ranks : common_colors_ranks) {
		for(const auto & index : ranks) {
			color_indices.push_back(index);
		}
	}
}

void Analysis::findSimilarity() {
	initializeHashTable();
	std::vector<unsigned> scores;

	for(const auto & language : path_languages) {
		for(unsigned i = 0; i < path_languages.size(); i++) {
			double score = similarityScore(matrices_[language.first], matrices_[english_indices[i]]);
			scores.push_back(score);
		}

		similarity[language.second] = scores;
		scores.clear();
	}
}

unsigned Analysis::similarityScore(Grid<std::string> & languageOne, Grid<std::string> languageTwo) {
	createEnglishData();

	std::vector<std::string> copy_one = languageOne.getElementsVector();
	std::vector<std::string> copy_two = languageTwo.getElementsVector();

	return similaritySum(copy_one, copy_two, kDimension);
}

unsigned Analysis::similaritySum(std::vector<std::string> & languageOne, std::vector<std::string> & languageTwo, unsigned index) {
	unsigned count = 0;

	for(unsigned i = 0; i < kDimension; i++) {
		for(unsigned j = 0; j < kDimension; j++) {
			if(languageOne[i] == languageTwo[j]) {
				count++;
			}
		}
	}

	if(index == kDimension * kDimension - kDimension) {
		return count;
	}

	return similaritySum(languageOne, languageTwo, index + kDimension);
}

void Analysis::createEnglishData() {
	for(const auto & index : english_indices) {
		for(unsigned i = 0; i < languages.size(); i++) {
			if(i == index) english_languages.push_back(languages[i]);
		}
	}
}

void Analysis::initializeHashTable() {
	for(unsigned i = 0; i < english_indices.size(); i++) {
		path_languages[english_indices[i]] = file_names[english_indices[i]];
	}
}

inline bool not_digit(char ch) {
    return '0' <= ch && ch <= '9';
}

void Analysis::cleanNumericalData(std::vector<std::string> & data) {
	for(unsigned i = 0; i < data.size(); i++) {
		std::string result = "";
		std::copy_if(data[i].begin(), data[i].end(), std::back_inserter(result), not_digit);
		data[i] = result;
	}
}

template <typename T>
void Analysis::writeFile(std::string name, std::vector<T> & data) {
	std::ofstream outFile(name);

	for(const auto & elem : data) {
		outFile << elem << "\r\n";
	}
}

int main() {
	Analysis inspect;

	inspect.averageFrequentWordLength();
	inspect.writeFile("../visual/data/average_frequent_word_length.txt", inspect.frequent_word_length);

	inspect.averageWordLength();
	inspect.writeFile("../visual/data/average_word_length.txt", inspect.word_length);
	
	inspect.mostCommonColor();
	inspect.writeFile("../visual/data/most_common_color.txt", inspect.color_results);
	inspect.writeFile("../visual/data/color_indices.txt", inspect.color_indices);

	inspect.findSimilarity();

	for(unsigned i = 0; i < inspect.similarity.size(); i++) {
		std::string language = inspect.file_names[inspect.english_indices[i]];
		inspect.writeFile("../visual/data/" + language + ".txt", inspect.similarity.at(language));
	}

	inspect.cleanNumericalData(inspect.english_frequency);
	inspect.writeFile("../visual/data/english_frequency.txt", inspect.english_frequency);

	return 0;
}