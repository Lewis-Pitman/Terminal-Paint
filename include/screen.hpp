#ifndef SCREEN
#define SCREEN

#include <string>
#include <array>
#include <vector>

enum lineType {
	//For readability
	dash,
	number
};

enum commandScreenType {
	//For readability
	root,
	file,
	tool,
	colour
};

enum consoleColour {
	//For use in SetConsoleAttribute()
	red = 0x40,
	yellow = 0x60,
	green = 0x20,
	blue = 0x10,
	white = 0x70,
	black = 0x00
};

class Screen {
public:
	//View dimensions
	static const int padding{ 3 };
	const std::pair<int, int> commandViewDimensions{ 20, 2 };
	const std::pair<int, int> inputViewDimensions{ 20, 1 };
	std::pair<int, int> mainViewDimensions;
	std::pair<int, int> alertViewDimensions;
	//The main view is the only one that actually uses the height value, however the others still have it just in case

private:
	//List of available commands
	const std::array<std::string, 3> rootCommands = { "file", "tool", "colour" };
	const std::array<std::string, 4> fileCommands = { "back", "new", "open", "export" };
	const std::array<std::string, 5> toolCommands = { "back", "brush", "line", "fill", "erase"};
	const std::array<std::string, 7> colourCommands = { "back", "red", "yellow", "green", "blue", "white", "black" };

	//A vector of colours, used for drawing the image
	static std::vector<consoleColour> pixels; // !!!!! Maybe change this to be included in a file.hpp and file.cpp!?

public:
	Screen(int mainViewX, int mainViewY);
	~Screen();

	void drawScreen();
	void resizeMainView(int width, int height, Screen* screenToResize);

private:
	//Misc-----------------------------------------------------
	inline void drawLine(int width, int padding, lineType type, bool breakLine);

	//Command View---------------------------------------------
	inline void printCommands(commandScreenType type);
	inline void drawCommandView(std::string title, std::string description);
	void drawCommandView(commandScreenType type);

	//Input View-----------------------------------------------
	void drawInputView();
	void drawInputView(std::string description);

	//Main View------------------------------------------------
	void drawMainView();
	void drawMainView(std::string title, std::string description); //Alert box in centre of screen

};

#endif
