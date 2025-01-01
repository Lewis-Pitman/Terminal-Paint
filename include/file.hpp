#ifndef PAINTFILE
#define PAINTFILE

#include <array>

#include "../include/enums.hpp"

/* Include functionality for :
* Saving to an external file
* Reading an external file and storing this read data in the pixels vector
* Creating a new file
*/

class File {
public:
	consoleColour* pixels;
	const int width;
	const int height;

public:
	File(int fileWidth, int fileHeight);
	File(int fileWidth, int fileHeight, consoleColour* openedFilePixels);
	~File();

	void openFile();
	void saveFile();
};

#endif