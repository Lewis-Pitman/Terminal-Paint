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
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case toolCommand:
			currentCommandScreen = tool;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case colourCommand:
			currentCommandScreen = colour;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		default:
			currentScreen->drawScreen("Command not recognised. Enter anything to dismiss");
			std::cin >> temp;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		}
	}
	else if (availableCommands == file) {
		switch (getCommand(command)) {
		case backCommand:
			currentCommandScreen = root;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case newCommand:
			currentScreen->resizeMainView(); //Screen has a built in function to do this

			delete currentFile;
			currentFile = new File(1, 1); //Replace w/ input
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case openCommand:
			currentScreen->drawScreen("Opening a file will delete the currently opened file. enter y to continue, or anything else to cancel");
			std::cin >> temp;

			if (temp == "y" || temp == "Y") {
				while(true){
					currentScreen->drawScreen("Enter the name of the file as it appears in the folder TPAINT saves");
					std::cin >> temp;
					if (currentFile->openFile(tpaintSavesDirectory + temp + ".TPAINT")) {
						break;
					}
					else {
						currentScreen->drawScreen("Something went wrong. Keep in mind the name is case sensitive. Enter anything to dismiss");
						std::cin >> temp;
					}
				}
			}

			currentScreen->drawScreen(currentCommandScreen);
			break;
		case saveCommand:
			currentScreen->drawScreen("Files are saved in the TPAINT saves folder in the same folder this exe is located. Enter a name:");
			std::cin >> temp;
			currentFile->saveFile(tpaintSavesDirectory + temp + ".TPAINT");
			
			currentScreen->drawScreen("Save successful. Enter anything to dismiss");
			std::cin >> temp;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case exportCommand:
			currentScreen->drawScreen("Exports are saved in the BMP exports folder in the same folder this exe is located. Enter a name:");
			std::cin >> temp;
			currentFile->exportFile(tpaintSavesDirectory + temp + ".TPAINT");

			currentScreen->drawScreen("Export successful. Enter anything to dismiss");
			std::cin >> temp;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		default:
			currentScreen->drawScreen("Command not recognised. Enter anything to dismiss");
			std::cin >> temp;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		}
	}
	else if (availableCommands == tool) {
		switch (getCommand(command)) {
		case backCommand:
			currentCommandScreen = root;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case brushCommand:
			currentScreen->drawScreen("Please enter the X coordinate of the pixel you'd like to brush");
			std::cin >> inputtedCoordinates.first;
			currentScreen->drawScreen("Please enter the Y coordinate of the pixel you'd like to brush");
			std::cin >> inputtedCoordinates.second;

			currentTool->fillSquare(inputtedCoordinates.first, inputtedCoordinates.second, currentFile, currentColour);
			currentScreen->drawScreen(currentCommandScreen);
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
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case fillCommand:
			currentScreen->drawScreen("Please enter the X coordinate of the pixel you'd like to fill");
			std::cin >> inputtedCoordinates.first;
			currentScreen->drawScreen("Please enter the Y coordinate of the pixel you'd like to fill");
			std::cin >> inputtedCoordinates.second;

			currentTool->fillTool(inputtedCoordinates.first, inputtedCoordinates.second, currentFile, currentColour);
			currentScreen->drawScreen(currentCommandScreen);
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
			currentScreen->drawScreen("Command not recognised. Enter anything to dismiss");
			std::cin >> temp;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		}
	}
	else if (availableCommands == colour) {
		switch (getCommand(command)) {
		case backCommand:
			currentCommandScreen = root;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case redCommand:
			currentColour = red;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case yellowCommand:
			currentColour = yellow;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case greenCommand:
			currentColour = green;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case blueCommand:
			currentColour = blue;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case whiteCommand:
			currentColour = white;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		case blackCommand:
			currentColour = black;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		default:
			currentScreen->drawScreen("Command not recognised. Enter anything to dismiss");
			std::cin >> temp;
			currentScreen->drawScreen(currentCommandScreen);
			break;
		}
	}
}
