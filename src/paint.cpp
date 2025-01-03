#include <iostream>
#include <filesystem>
#include <string>

#include "../include/paint.hpp"
#include "../include/enums.hpp"

std::string temp; //This is used to pause the program to allow the user to view a message

//Tool variables
std::pair<int, int> inputtedCoordinates;
std::pair<int, int> startPixelCoords;
std::pair<int, int> endPixelCoords;

Paint::Paint() {
	currentFile = new File(20, 20);
	currentScreen = new Screen(currentFile);
	currentTool = new Tool();

	//Create directories if they do not exist
	if (!std::filesystem::exists(tpaintSavesDirectory)) {
		std::filesystem::create_directory(tpaintSavesDirectory);
	}

	if (!std::filesystem::exists(bmpExportsDirectory)) {
		std::filesystem::create_directory(bmpExportsDirectory);
	}
}

Paint::~Paint() {
	delete currentFile;
	delete currentScreen;
	delete currentTool;
}

void Paint::Run() {
	std::string inputtedCommand{ "" };

	//!!!! convert command to lowercase!!

	currentScreen->drawScreen(currentCommandScreen);

	while (true){
		std::cin >> inputtedCommand;
		handleInput(inputtedCommand, currentCommandScreen);
	}
}

command Paint::getCommand(std::string command) {
	//Switch case does not support a string
	//This is an efficient alternative to get an enum from a string
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
			currentScreen->drawScreen("Command not recognised. Enter anything to dismiss");
			std::cin >> temp;
			break;
		}
		currentScreen->drawScreen(currentCommandScreen);
	}
	else if (availableCommands == file) {
		switch (getCommand(command)) {
		case backCommand:
			currentCommandScreen = root;
			break;
		case newCommand:
			currentScreen->drawScreen("Creating a file deletes the current one. Y to continue");
			std::cin >> temp;

			if (temp == "y" || temp == "Y") {
				int newWidth = 0;
				currentScreen->drawScreen("Enter the width of the file (Max 45)");
				std::cin >> newWidth;

				int newHeight = 0;
				currentScreen->drawScreen("Enter the height of the file (Max 45");
				std::cin >> newHeight;

				if (newWidth > 45 || newHeight > 45 || newWidth < 1 || newHeight < 1) {
					currentScreen->drawScreen("Invalid. X & Y cannot be less than 1 or bigger than 45. Enter anything to dismiss");
					std::cin >> temp;
				}
				else {
					delete currentFile;
					currentFile = new File(newWidth, newHeight);

					delete currentScreen;
					currentScreen = new Screen(currentFile);
				}
			}
			break;
		case openCommand:
			currentScreen->drawScreen("Opening a file will delete the currently opened file. Enter y to continue");
			std::cin >> temp;

			if (temp == "y" || temp == "Y") {
				currentScreen->drawScreen("Enter the name of the file as it appears in the folder TPAINT saves");
				std::cin >> temp;
				currentFile->openFile(tpaintSavesDirectory + temp + ".TPAINT");

				delete currentScreen;
				currentScreen = new Screen(currentFile);
			}
			break;
		case saveCommand:
			currentScreen->drawScreen("Files are saved in the TPAINT saves folder in the same folder this exe is located. Enter a name:");
			std::cin >> temp;
			currentFile->saveFile(tpaintSavesDirectory + temp + ".TPAINT");
			
			currentScreen->drawScreen("Save successful. Enter anything to dismiss");
			std::cin >> temp;
			break;
		case exportCommand:
			currentScreen->drawScreen("Exports are saved in the BMP exports folder in the same folder this exe is located. Enter a name:");
			std::cin >> temp;
			currentFile->exportFile(tpaintSavesDirectory + temp + ".TPAINT");

			currentScreen->drawScreen("Export successful. Enter anything to dismiss");
			std::cin >> temp;
			break;
		default:
			currentScreen->drawScreen("Command not recognised. Enter anything to dismiss");
			std::cin >> temp;
			break;
		}
		currentScreen->drawScreen(currentCommandScreen);
	}
	else if (availableCommands == tool) {
		switch (getCommand(command)) {
		case backCommand:
			currentCommandScreen = root;
			break;
		case brushCommand:
			currentScreen->drawScreen("Please enter the X coordinate of the pixel you'd like to brush");
			std::cin >> inputtedCoordinates.first;
			currentScreen->drawScreen("Please enter the Y coordinate of the pixel you'd like to brush");
			std::cin >> inputtedCoordinates.second;

			currentTool->fillSquare(inputtedCoordinates.first, inputtedCoordinates.second, currentFile, currentColour);
			break;
		case lineCommand:
			currentScreen->drawScreen("Please enter the X coordinate of the start pixel");
			std::cin >> startPixelCoords.first;
			currentScreen->drawScreen("Please enter the Y coordinate of the start pixel");
			std::cin >> startPixelCoords.second;

			currentScreen->drawScreen("Please enter the X coordinate of the end pixel");
			std::cin >> endPixelCoords.first;
			currentScreen->drawScreen("Please enter the Y coordinate of the end pixel");
			std::cin >> endPixelCoords.second;

			currentTool->lineTool(startPixelCoords, endPixelCoords, currentFile, currentColour);
			break;
		case fillCommand:
			currentScreen->drawScreen("Please enter the X coordinate of the pixel you'd like to fill");
			std::cin >> inputtedCoordinates.first;
			currentScreen->drawScreen("Please enter the Y coordinate of the pixel you'd like to fill");
			std::cin >> inputtedCoordinates.second;

			currentTool->fillTool(inputtedCoordinates.first, inputtedCoordinates.second, currentFile, currentColour);
			break;
		case eraseCommand:
			if (erasing) {
				erasing = false;
				currentColour = erasingTemp;
				currentScreen->drawScreen("Erase was turned off. Enter anything to dismiss");
				std::cin >> temp;
			}
			else {
				erasing = true;
				erasingTemp = currentColour;
				currentColour = black;
				currentScreen->drawScreen("Erase was turned on. Enter anything to dismiss");
				std::cin >> temp;
			}


			break;
		default:
			currentScreen->drawScreen("Command not recognised. Enter anything to dismiss");
			std::cin >> temp;
			break;
		}
		currentScreen->drawScreen(currentCommandScreen);
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
			currentScreen->drawScreen("Command not recognised. Enter anything to dismiss");
			std::cin >> temp;
			break;
		}
		currentScreen->drawScreen(currentCommandScreen);
	}
}
