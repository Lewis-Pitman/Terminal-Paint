#ifndef SCREEN
#define SCREEN

#include <string>
#include <array>
#include <vector>
#include <Windows.h>

#include "../include/enums.hpp"
#include "../include/file.hpp"

class Screen {
private:
	//View dimensions
	static const int padding{ 3 };
	const std::pair<int, int> commandViewDimensions{ 20, 2 };
	std::pair<int, int> mainViewDimensions;
	std::pair<int, int> alertViewDimensions;
	//The main view is the only one that actually uses the height value, however the others still have it just in case

	File* openedFile = nullptr;

private:
	//List of available commands
	const std::array<std::string, 3> rootCommands = { "file", "tool", "colour" };
	const std::array<std::string, 5> fileCommands = { "back", "new", "open", "save", "export" };
	const std::array<std::string, 5> toolCommands = { "back", "brush", "line", "fill", "erase"};
	const std::array<std::string, 7> colourCommands = { "back", "red", "yellow", "green", "blue", "white", "black" };


	const WORD defaultTerminalColours = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //So we can change colour easily to print everything outside the main view (White text, black bg)

public:
	Screen(File* file);
	~Screen();

	void drawScreen(commandScreenType commandType); //Used to control the command screen (Whether it displays root, file, colour etc)
	void drawScreen(std::string message); //Used for pop-up dialogue above the main screen

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
};

#endif
