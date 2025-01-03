#ifndef PAINTFILE
#define PAINTFILE

#include <array>
#include <string>

#include "../include/enums.hpp"

/* Include functionality for :
* Saving to an external file
* Reading an external file and storing this read data in the pixels vector
* Creating a new file
*/

class File {
public:
	consoleColour* pixels;
	int width;
	int height;

public:
	File(int fileWidth, int fileHeight);
	File(int fileWidth, int fileHeight, consoleColour* openedFilePixels);
	~File();

	bool openFile(std::string directory);
	void saveFile(std::string directory);
	void exportFile(std::string directory);
};

#endif