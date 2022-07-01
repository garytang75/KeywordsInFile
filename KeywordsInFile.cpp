/*KeywordsInFile.cpp
updated all the functions to be const
*/

#include "KeywordsInFile.h"
#include <cstdlib> //exist() for error checking when opening a file






//required constructor, filename as parameter
KeywordsInFile::KeywordsInFile(std::string& filename_with_keywords, std::string& filename_with_text) {
	//file_with_key opens and read the file
	std::ifstream file_with_key(filename_with_keywords);
	//error checking, if not opened, cout error and terminate the program
	if (!file_with_key.is_open()) {
		std::cout << "Error, can not open file. \n";
		exit(1);
	}
	//extract word from line
	while (std::getline(file_with_key, line)) {
		line.append("\n");
		for (size_t i = 0; i < line.length(); i++) {
			//extra checking in case isalpha fail(which is unlikely)
			//char put in word

			//if (isalpha(line[i])&&line[i] != '\n') gives assertion error, so implemented own logic
			if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z'))
			{
				word += line[i];
			}
			//if non alphabetic char scanned
			//return the word and insert in unordered_map
			else {
				if (!word.empty()) {
					umap.insert({ word, std::unordered_map<int,int>() });
					//everything starts in line 1 with 0 occurence in the key file
					umap.at(word).insert({ 1,0 });
					//insert word in total occurence map
					omap.insert({ word, 0});
					//reset word for the next word
					word = "";
				}
			}
		}
	}
	//close file_with_key
	file_with_key.close();
	//reset word one more time to ensure no error
	word = "";
	//initate line_number to 1
	int line_number = 1;



	//file_with_text open and read text file
	std::ifstream file_with_text(filename_with_text);
	//error checking, if not opened, cout error and terminate the program
	if (!file_with_text.is_open()) {
		std::cout << "Error, can not open text file. \n";
		exit(1);
	}
	//extract word and count word
	while (std::getline(file_with_text, line)) {
		line.append("\n");
		for (size_t i = 0; i < line.length();i++) {
			//if (isalpha(line[i]) && line[i] != '/n') gives assertion error,although works, so implemented own logic
			if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z'))
			{
				word += line[i];
			}
			else {
				if (!word.empty()) {
					//if word existed
					if (KeywordFound(word)) {
						//total_occurence ++
						omap.at(word)++;
					}
					//if word existed
					if (KeywordFound(word)) {
						//if the line number matched, else insert line number
						if (umap.at(word).count(line_number)) {
							//total in line ++
							umap.at(word).at(line_number)++;
						}
						else {
							umap.at(word).insert({ line_number,1 });
						}
					}
					//reset word
					word = "";
				}
			}
		}
		//reset word
		word = "";
		//line_number++
		line_number++;
	}
	//close text file
	file_with_text.close();
}


//returns true if keyword is found in the text, otherwise return false
bool KeywordsInFile::KeywordFound(const std::string& keyword) const {
	return umap.count(keyword);
}


//returns the total of the keyword in line number
int KeywordsInFile::KeywordsInLine(const std::string& keyword, const int& line_number)const{
	if (umap.count(keyword)){
		return umap.at(keyword).at(line_number);
	}
	return 0;
}



//returns the total occurrences of keyword in the entire text
int KeywordsInFile::TotalOccurrences(const std::string& keyword)const{
	if (omap.count(keyword)) {
		return omap.at(keyword);
	}
	return 0;
}





//operator << overload, iterate thru the unordered_map, and print the content(keyworsinline and totaloccurrences)
std::ostream& operator << (std::ostream& os, const KeywordsInFile& k) {

	for (const auto& x : k.omap) {
		os << x.first << " has " << x.second << " occurence(s) throuhout the text. \n";
	}

	for (const auto& y : k.umap) {
		for (const auto& z : y.second) {
			//if in line there is no occurences, no print for organized purposes
			if (z.second != 0) {
				os << y.first << " in line " << z.first << " has " << z.second << " occurence(s). \n";
			}
		}
	}



	return os;
}

