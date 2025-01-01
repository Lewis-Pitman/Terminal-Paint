#include <string>

#include "../include/paint.hpp"
#include "../include/enums.hpp"

void Paint::Run() {
	while (true){
		//Add main loop
	}
}

command Paint::getCommand(std::string command) {
	auto it = commandMap.find(command);
	if (it != commandMap.end()) {
		return it->second;
	}
}

void Paint::handleInput(std::string command, commandScreenType availableCommands) {
	if (availableCommands == root) {
		switch (getCommand(command)) {
		case fileCommand:
			currentCommandScreen = file;
			break;
		case toolCommand:
			currentCommandScreen = tool;
			break;
		case colourCommand:
			currentCommandScreen = colour;
			break;
		default:
			//Not recognised message
			break;
		}
	}
	else if (availableCommands == file) {
		switch (getCommand(command)) {
		case backCommand:
			currentCommandScreen = root;
			break;
		case newCommand:
			//UI to get dimensions

			delete currentFile;
			currentFile = new File(1, 1); //Replace w/ input
			//Refresh screen

			break;
		case openCommand:
			//UI to get directory/name of file in generated directory..?

			currentFile->openFile(); //Add a parameter for directory
			break;
		case saveCommand:
			//UI to get directory

			currentFile->saveFile(); //Add a parameter for directory

			//UI to indicate it was successful/unsuccessful
			break;
		case exportCommand:
			break;
		default:
			//Not recognised message
			break;
		}
	}
	else if (availableCommands == tool) {
		switch (getCommand(command)) {
		case backCommand:
			currentCommandScreen = root;
			break;
		case brushCommand:
			//Logic to get screen object and invoke brush
			break;
		case lineCommand:
			//Logic to get screen object and invoke line
			break;
		case fillCommand:
			//Logic to get screen object and invoke fill
			break;
		case eraseCommand:
			if (erasing) {
				erasing = false;
				currentColour = erasingTemp;
			}
			else {
				erasing = true;
				erasingTemp = currentColour;
				currentColour = black;
			}
			break;
		default:
			//Not recognised message
			break;
		}
	}
	else if (availableCommands == colour) {
		switch (getCommand(command)) {
		case backCommand:
			currentCommandScreen = root;
			break;
		case redCommand:
			currentColour = red;
			break;
		case yellowCommand:
			currentColour = yellow;
			break;
		case greenCommand:
			currentColour = green;
			break;
		case blueCommand:
			currentColour = blue;
			break;
		case whiteCommand:
			currentColour = white;
			break;
		case blackCommand:
			currentColour = black;
			break;
		default:
			//Not recognised message
			break;
		}
	}
}