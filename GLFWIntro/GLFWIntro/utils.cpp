#include "utils.h"
#include <fstream>

void readFile(const char* path, char** fileData)
{
	/// source : https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
	std::ifstream t;
	int length;
	t.open(path);
	t.seekg(0, std::ios::end);
	length = t.tellg();
	t.seekg(0, std::ios::beg);

	if (*fileData)
		delete *fileData;
	*fileData = new char[length];
	t.read(*fileData, length);
	t.close();
}