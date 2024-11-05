#ifndef SCREEN
#define SCREEN

#include <string>

enum lineType {
	dash,
	number
};

enum consoleColour {
	red = 41,
	yellow = 43,
	green = 42,
	blue = 44,
	white = 47,
	black = 40
};

class screen {
public:
	const std::array<std::string, 3> rootCommands = { "file", "tool", "colour" };
	const std::array<std::string, 4> fileCommands = { "back", "new", "open", "export"};
	const std::array<std::string, 4> toolCommands = { "back", "brush", "line", "fill" };
	const std::array<std::string, 7> colourCommands = { "back", "red", "yellow", "green", "blue", "white", "black"};

	const std::pair<int width, int height> commandViewDimensions;
	const std::pair<int width, int height> mainViewDimensions;
	const std::pair<int width, int height> inputViewDimensions;
public:
	screen(std::pair<int commandWidth, int commandHeight> commandDimensions, std::pair<int viewWidth, int viewHeight> viewDimensions, std::pair<int inputWidth, int inputHeight> inputDimensions);
	~screen();

	drawScreen();

protected:
	drawLine(int width, int padding, int type);

private:
	drawCommandView();
};


#endif
