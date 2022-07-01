/*
KeywordsInFile.h
*/

#ifndef _KEYWORDSINFILE_H_
#define _KEYWORDSINFILE_H_



#include <iostream>
#include <unordered_map> 
#include <string>  //std::string
#include <fstream> //std::ifstream
#include <ctype.h> //isalpha()(error)



class KeywordsInFile {
public:
	/*functions required for the project*/
	//disable the default constructor(non parametrized constructor)
	KeywordsInFile() = delete;
	//required constructor, filename as parameter
	KeywordsInFile(std::string& file_with_keywords, std::string& file_with_text);
	//returns true if keyword is found in the text, otherwise return false
	bool KeywordFound(const std::string& keyword) const;
	//returns the total of the keyword in line number
	int KeywordsInLine(const std::string& keyword, const int& line_number)const;
	//returns the total occurrences of keyword in the entire text
	int TotalOccurrences(const std::string& keyword)const;
	//operator << overload, iterate thru the unordered_map, and print the content(keyworsinline and totaloccurrences)
	friend std::ostream& operator << (std::ostream& os, const KeywordsInFile& k);

private:
	//line for getline()
	std::string line;
	//use for extract word in the text file
	std::string word; 
	//for KeywordsInLine, <word, line_number, total>
	std::unordered_map < std::string, std::unordered_map<int, int>>umap;
	//for TotalOccurrences <word, total>
	std::unordered_map<std::string, int> omap;

};


#endif