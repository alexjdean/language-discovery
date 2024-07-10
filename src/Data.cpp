#include "Data.h"

LanguageData::LanguageData() {/* Nothing to see here */}

void LanguageData::readFileIn(std::string filePath) {
	std::string line = "";
	std::ifstream file_path(filePath);

	_addContents(file_path, line, data_);
	_removeWhiteSpace(data_);
}

void LanguageData::_addContents(std::ifstream & file, std::string & line, std::vector<std::string> & data) {
	if(file.is_open()) {
		while(getline(file, line)) {
			data.push_back(line);
		}

		file.close();
	}
}

void LanguageData::_removeWhiteSpace(std::vector<std::string> & data) {
	for(auto & elem : data) {
		elem.erase(remove_if(elem.begin(), elem.end(), isspace), elem.end());
		std::transform(elem.begin(), elem.end(), elem.begin(), ::tolower);
	}
}