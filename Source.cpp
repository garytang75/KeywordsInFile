
#include "KeywordsInFile.h"

int main()
{
	std::string keywordFile = "key.txt";
	std::string textFile = "Text.txt";

	KeywordsInFile kif1(keywordFile, textFile);

	std::cout << kif1 << std::endl;

	return 0;
}

