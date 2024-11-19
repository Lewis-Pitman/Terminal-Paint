#ifndef FILE
#define FILE

#include <vector>

#include "../include/enums.hpp"

/* Include functionality for :
* Saving to an external file
* Reading an external file and storing this read data in the pixels vector
* Creating a new file
*/

class File {
public:
	std::vector<consoleColour> pixels;
	const int width;
	const int height; 

public:
	File(int fileWidth, int fileHeight);
	~File();

	std::vector<consoleColour> openFile();
	std::vector<consoleColour> saveFile();
};

#endif