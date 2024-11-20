#ifndef SCREEN
#define SCREEN

#include <string>
#include <array>
#include <vector>
#include <Windows.h>

#include "../include/enums.hpp"
#include "../include/file.hpp"

class Screen {
public:
	//View dimensions
	static const int padding{ 3 };
	const std::pair<int, int> commandViewDimensions{ 20, 2 };
	std::pair<int, int> mainViewDimensions;
	std::pair<int, int> alertViewDimensions;
	//The main view is the only one that actually uses the height value, however the others still have it just in case

private:
	//List of available commands
	const std::array<std::string, 3> rootCommands = { "file", "tool", "colour" };
	const std::array<std::string, 4> fileCommands = { "back", "new", "open", "export" };
	const std::array<std::string, 5> toolCommands = { "back", "brush", "line", "fill", "erase"};
	const std::array<std::string, 7> colourCommands = { "back", "red", "yellow", "green", "blue", "white", "black" };

	File* openedFile = nullptr;

	const WORD defaultTerminalColours = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //So we can change colour easily to print everything outside the main view (White text, black bg)

public:
	Screen(File file);
	~Screen();

	void drawScreen();
	void resizeMainView();

private:
	//Misc-----------------------------------------------------
	inline void drawLine(int width, int padding, lineType type, bool breakLine);

	//Command View---------------------------------------------
	inline void printCommands(commandScreenType type);
	inline void drawCommandView(std::string title, std::string description);
	void drawCommandView(commandScreenType type);

	//Box View-----------------------------------------------
	void drawBoxView(int width, std::string description);

	//Main View------------------------------------------------
	void drawMainView();
	void drawMainView(std::string title, std::string description); //Alert box in centre of screen
	void resizeMainView(int width, int height, Screen* currentScreen);
};

#endif
