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
				std::cin >> temp;
				try {
					newWidth = std::stoi(temp);
				}
				catch (const std::exception&) {
					currentScreen->drawScreen("Please enter a number. Enter anything to dismiss");
					std::cin >> temp;
					break;
				}

				int newHeight = 0;
				currentScreen->drawScreen("Enter the height of the file (Max 45)");
				std::cin >> temp;
				try {
					newHeight = std::stoi(temp);
				}
				catch (const std::exception&) {
					currentScreen->drawScreen("Please enter a number. Enter anything to dismiss");
					std::cin >> temp;
					break;
				}

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

				if (currentFile->openFile(tpaintSavesDirectory + temp + ".TPAINT")) {
					delete currentScreen;
					currentScreen = new Screen(currentFile);
				}
				else {
					currentScreen->drawScreen("Error. Name is case sensitive, and don't include .TPAINT. Enter anything to dismiss.");
					std::cin >> temp;
				}
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
			std::cin >> temp;
			try {
				inputtedCoordinates.first = std::stoi(temp);
			}
			catch (const std::exception&) {
				currentScreen->drawScreen("Please enter a number. Enter anything to dismiss");
				std::cin >> temp;
				break;
			}
			currentScreen->drawScreen("Please enter the Y coordinate of the pixel you'd like to brush");
			std::cin >> temp;
			try {
				inputtedCoordinates.second = std::stoi(temp);
			}
			catch (const std::exception&) {
				currentScreen->drawScreen("Please enter a number. Enter anything to dismiss");
				std::cin >> temp;
				break;
			}

			if (inputtedCoordinates.first >= 1 && inputtedCoordinates.first <= currentFile->width &&
				inputtedCoordinates.second >= 1 && inputtedCoordinates.second <= currentFile->height) {
				currentTool->fillSquare(inputtedCoordinates.first, inputtedCoordinates.second, currentFile, currentColour);
			}
			else {
				currentScreen->drawScreen("Coordinates provided weren't valid. Enter anything to dismiss");
				std::cin >> temp;
			}
			break;

		case lineCommand:
			currentScreen->drawScreen("Please enter the X coordinate of the start pixel");
			std::cin >> temp;
			try {
				startPixelCoords.first = std::stoi(temp);
			}
			catch (const std::exception&) {
				currentScreen->drawScreen("Please enter a number. Enter anything to dismiss");
				std::cin >> temp;
				break;
			}
			currentScreen->drawScreen("Please enter the Y coordinate of the start pixel");
			std::cin >> temp;
			try {
				startPixelCoords.second = std::stoi(temp);
			}
			catch (const std::exception&) {
				currentScreen->drawScreen("Please enter a number. Enter anything to dismiss");
				std::cin >> temp;
				break;
			}

			if (startPixelCoords.first >= 1 && startPixelCoords.first <= currentFile->width &&
				startPixelCoords.second >= 1 && startPixelCoords.second <= currentFile->height) {
				currentScreen->drawScreen("Please enter the X coordinate of the end pixel");
				std::cin >> temp;
				try {
					endPixelCoords.first = std::stoi(temp);
				}
				catch (const std::exception&) {
					currentScreen->drawScreen("Please enter a number. Enter anything to dismiss");
					std::cin >> temp;
					break;
				}
				currentScreen->drawScreen("Please enter the Y coordinate of the end pixel");
				std::cin >> temp;
				try {
					endPixelCoords.second = std::stoi(temp);
				}
				catch (const std::exception&) {
					currentScreen->drawScreen("Please enter a number. Enter anything to dismiss");
					std::cin >> temp;
					break;
				}

				if (endPixelCoords.first >= 1 && endPixelCoords.first <= currentFile->width &&
					endPixelCoords.second >= 1 && endPixelCoords.second <= currentFile->height) {
					currentTool->lineTool(startPixelCoords, endPixelCoords, currentFile, currentColour);
				}
				else {
					currentScreen->drawScreen("Coordinates provided weren't valid. Enter anything to dismiss");
					std::cin >> temp;
				}
			}
			else {
				currentScreen->drawScreen("Coordinates provided weren't valid. Enter anything to dismiss");
				std::cin >> temp;
			}
			break;

		case fillCommand:
			currentScreen->drawScreen("Please enter the X coordinate of the pixel you'd like to fill");
			std::cin >> temp;
			try {
				inputtedCoordinates.first = std::stoi(temp);
			}
			catch (const std::exception&) {
				currentScreen->drawScreen("Please enter a number. Enter anything to dismiss");
				std::cin >> temp;
				break;
			}
			currentScreen->drawScreen("Please enter the Y coordinate of the pixel you'd like to fill");
			std::cin >> temp;
			try {
				inputtedCoordinates.second = std::stoi(temp);
			}
			catch (const std::exception&) {
				currentScreen->drawScreen("Please enter a number. Enter anything to dismiss");
				std::cin >> temp;
				break;
			}

			if (inputtedCoordinates.first >= 1 && inputtedCoordinates.first <= currentFile->width &&
				inputtedCoordinates.second >= 1 && inputtedCoordinates.second <= currentFile->height) {
				currentTool->fillTool(inputtedCoordinates.first, inputtedCoordinates.second, currentFile, currentColour);
			}
			else {
				currentScreen->drawScreen("Coordinates provided weren't valid. Enter anything to dismiss");
				std::cin >> temp;
			}
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
