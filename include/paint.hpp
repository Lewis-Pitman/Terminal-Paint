#ifndef PAINT
#define PAINT

#include <string>
#include <unordered_map>
#include <filesystem>

#include "../include/enums.hpp"
#include "../include/file.hpp"
#include "../include/screen.hpp"
#include "../include/tools.hpp"

class Paint {

public:
	std::string inputtedCommand{ "" };

private:
	//Components -> Consists of a file, a screen, and a tool
	File* currentFile;
	Screen* currentScreen;
	Tool* currentTool;

	//Variables
	commandScreenType currentCommandScreen{root};
	consoleColour currentColour{ red };

	bool erasing;
	consoleColour erasingTemp{white};

	std::string rootDirectory = std::filesystem::current_path().root_path().string();
	std::string tpaintSavesDirectory = rootDirectory + "\\TPAINT saves";
	std::string bmpExportsDirectory = rootDirectory + "\\BMP exports";

	//Command map for processing input
	std::unordered_map<std::string, command> commandMap = {
		{"back", backCommand},
		{"file", fileCommand},
		{"tool", toolCommand},
		{"colour", colourCommand},
		{"new", newCommand},
		{"open", openCommand},
		{"save", saveCommand},
		{"export", exportCommand},
		{"brush", brushCommand},
		{"line", lineCommand},
		{"fill", fillCommand},
		{"erase", eraseCommand},
		{"red", redCommand},
		{"yellow", yellowCommand},
		{"green", greenCommand},
		{"blue", blueCommand},
		{"white", whiteCommand},
		{"black", blackCommand},
	};


public:
	Paint();
	~Paint();

	void Run();

private:
	command getCommand(std::string command);
	void handleInput(std::string command, commandScreenType availableCommands);
};

#endif
