#ifndef TOOLS
#define TOOLS

class tool {
public:
	static int colour;
	static bool erasing;

public:
	tool();
	~tool();

protected:
	fillSquare(const int xCoord, const int yCoord);
	fillSquare(const &std::pair<int xCoord, int yCoord>);
};

class brush : tool {

};

class line : tool {

};

class fill : tool {

};

#endif
