#ifndef PAINT
#define PAINT

#include <string>
#include <unordered_map>

#include "../include/enums.hpp"
#include "../include/file.hpp"

class Paint {

public:
	std::string inputtedCommand{ "" };

private:
	std::unordered_map<std::string, command> commandMap = {
		{"back", backCommand},
		{"file", fileCommand},
		{"tool", toolCommand},
		{"colour", colourCommand},
		{"new", newCommand},
		{"open", openCommand},
		{"save", saveCommand},
		{"export", exportCommand},
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

	commandScreenType currentCommandScreen{root};
	File* currentFile = new File(20, 20);

	consoleColour currentColour;

	bool erasing;
	consoleColour erasingTemp{white};

public:
	Paint();
	~Paint();

	void Run();

private:
	command getCommand(std::string command);
	void handleInput(std::string command, commandScreenType availableCommands);
};

#endif
