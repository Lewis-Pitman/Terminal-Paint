#ifndef TOOLS
#define TOOLS

#include <utility>
#include <vector>

#include "../include/enums.hpp"
#include "../include/file.hpp"

class Tool {
public:
	static int colour;
	static bool erasing;

public:
	Tool();
	~Tool();

//protected:
	void fillSquare(const int xCoord, const int yCoord, File *&currentFile, consoleColour colour);
	void fillSquare(const std::vector<std::pair<int, int>> coords, File *&currentFile, consoleColour colour);
};

class Brush : Tool {

};

class Line : Tool {
	
};

class Fill : Tool {

};

#endif
