#ifndef SCREEN
#define SCREEN

#include <string>
#include <array>

enum lineType {
	//For readability
	dash,
	number
};

enum consoleColour {
	//For use in SetConsoleAttribute()
	red = 41,
	yellow = 43,
	green = 42,
	blue = 44,
	white = 47,
	black = 40
};

class screen {
public:
	//List of usable commands
	const std::array<std::string, 3> rootCommands = { "file", "tool", "colour" };
	const std::array<std::string, 4> fileCommands = { "back", "new", "open", "export"};
	const std::array<std::string, 4> toolCommands = { "back", "brush", "line", "fill" };
	const std::array<std::string, 7> colourCommands = { "back", "red", "yellow", "green", "blue", "white", "black"};

	//View dimensions
	const int padding{ 3 };
	const std::pair<int, int> commandViewDimensions{ 20, 3 };
	const std::pair<int, int> mainViewDimensions{ 20, 18 };
	const std::pair<int, int> inputViewDimensions{ 20, 1 };
public:
	//screen();
	//~screen();

	void drawScreen();

protected:
	inline void drawLine(int width, int padding, lineType type);
	inline int printArray(const char* arrayToPrint);

private:
	void drawCommandView();
};

#endif
