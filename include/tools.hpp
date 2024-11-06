#ifndef TOOLS
#define TOOLS

#include <utility>

class tool {
public:
	static int colour;
	static bool erasing;

public:
	tool();
	~tool();

protected:
	void fillSquare(const int xCoord, const int yCoord);
	void fillSquare(const std::pair<int, int>& coords);
};

class brush : tool {

};

class line : tool {

};

class fill : tool {

};

#endif
