#include <iostream>
#include <iomanip>
#include <ios>
#
#include <array>
#include <Windows.h>
#include <stdlib.h>

#include "../include/screen.hpp"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Used for setting colour of the terminal

Screen::Screen(int mainViewX, int mainViewY) { //constructor
	static std::vector<consoleColour> pixels; 
	mainViewDimensions = { mainViewX, mainViewY };

	//Capping the size of the alert box based on the size of the main screen:
	alertViewDimensions.first = (mainViewX >= 20) ? 10 : mainViewX / 2; 
	alertViewDimensions.second = (mainViewY >= 20) ? 8 : mainViewY / 2; 

	pixels.reserve(50 * 50); //Reserve the memory needed for the maximum size.
}

Screen::~Screen() {} //Deconstructor

void Screen::resizeMainView(int width, int height, Screen* screenToResize) {

	//DOES NOT WORK!!! FIX! -------------------------------------------------


	//Validation:
	if (width > 50 || width < 8) {
		system("CLS");
		drawCommandView("Resize", "Enter a width (Min 8, Max 50)");
		drawMainView("This width is not valid.", "Please enter dimensions again");
		std::cout << "Width >>> ";
		//Code to handle input (Placeholder for now)
		int newWidth = 0;
		std::cin >> newWidth;

		system("CLS");
		drawCommandView("Resize", "Enter a height (Min 16, Max 50)");
		drawMainView("Please enter the height", "of your new file.");
		std::cout << "Height >>> ";

		int newHeight = 0;
		std::cin >> newHeight;

		resizeMainView(newWidth, newHeight, screenToResize);
	}
	else if (height > 50 || height < 16) {
		system("CLS");
		drawCommandView("Resize", "Enter a width (Min 8, Max 50)");
		drawMainView("This height is not valid.", "Please enter dimensions again");
		std::cout << "Width >>> ";
		//Code to handle input (Placeholder for now)

		int newWidth = 0;
		std::cin >> newWidth;

		system("CLS");
		drawCommandView("Resize", "Enter a height (Min 16, Max 50)");
		drawMainView("Please enter the height", "of your new file.");
		std::cout << "Height >>> ";

		int newHeight = 0;
		std::cin >> newHeight;

		resizeMainView(newWidth, newHeight, screenToResize);
	}
	else {
		delete screenToResize;
		screenToResize = new Screen(width, height);
		drawScreen();
	//Code to clear pixels vector -------------(placeholder)-------------
	}
}

inline void Screen::drawLine(int width, int padding, lineType type, bool breakLine) {
	if (breakLine) {
		if (type == dash) {
			std::cout << "\n";
			for (int i = 0; i < (width * padding) + 1; i++) {
				std::cout << "-";
			}
		}
		else{
			std::cout << "\n";
			for (int i = 0; i < width; i++) {
				std::cout << std::setw(padding) << i + 1;
			}
		}
		std::cout << "\n";
	}
	else {
		if (type == dash) {
			for (int i = 0; i < (width * padding) + 1; i++) {
				std::cout << "-";
			}
		}
		else {
			for (int i = 0; i < width; i++) {
				std::cout << std::setw(padding) << i + 1;
			}
		}
	}
}

//Command Screen--------------------------------------------------------------------------------------------------------------------

inline void Screen::printCommands(commandScreenType type) { 

	std::string commandString = "";

	switch (type) {
	case root:
		for (int i = 0; i < rootCommands.size(); i++) {
			commandString += rootCommands[i] + ", ";
		}
		break;
	case file:
		for (int i = 0; i < fileCommands.size(); i++) {
			commandString += fileCommands[i] + ", ";
		}
		break;
	case tool:
		for (int i = 0; i < toolCommands.size(); i++) {
			commandString += toolCommands[i] + ", ";
		}
		break;
	case colour:
		for (int i = 0; i < colourCommands.size(); i++) {
			commandString += colourCommands[i] + ", ";
		}
		break;
	}
	
	commandString[commandString.size() - 2] = ' '; //Remove the comma on the last command
	std::cout << commandString << std::setw((commandViewDimensions.first * padding) - commandString.length()) << "|";

}

inline void Screen::drawCommandView(commandScreenType type) {
	drawLine(commandViewDimensions.first, padding, dash, true);
	std::cout << "|Available commands:" << std::setw((commandViewDimensions.first * padding) - 19) << "|";
	std::cout << "\n|";
	printCommands(type);
	drawLine(commandViewDimensions.first, padding, dash, true);
}

inline void Screen::drawCommandView(std::string title, std::string description) { //Overload for a custom title and description
	drawLine(commandViewDimensions.first, padding, dash, true);
	std::cout << "|";
	std::cout << title << std::setw((commandViewDimensions.first * padding) - title.length()) << "|";
	std::cout << "\n|";
	std::cout << description << std::setw((commandViewDimensions.first * padding) - description.length()) << "|";
	drawLine(commandViewDimensions.first, padding, dash, true);
}

//---------------------------------------------------------------------------------------------------------------------------------

//Main Screen----------------------------------------------------------------------------------------------------------------------

void Screen::drawMainView() {
	std::cout << "\n";
	drawLine(mainViewDimensions.first, padding, number, false);
	drawLine(mainViewDimensions.first, padding, dash, true);

	std::cout << "|";
	for (int i = 0; i < mainViewDimensions.second - 1; i++) {
		for (int j = 0; j < mainViewDimensions.first - 1; j++) {
			//SetConsoleTextAttribute(hConsole, white); <-- Test implementation (Not working)
			//SetConsoleTextAttribute(hConsole, pixels[(lineNumber * mainViewDimensions.first) + j]); <-- Implementation using pixels vector (Not working)
			std::cout << std::setw(padding);
			std::cout << "."; //A character needs to be present here to format the box correctly. Using spaces or leaving it blank does not function correctly.
			std::cout << std::setw(padding);
		}
		//SetConsoleTextAttribute(hConsole, black); <-- If this were not here, the entire width of the terminal would be set to the last used colour.
		std::cout << "  .| " << i + 1;
		std::cout << "\n|";
	}

	//Final line
	for (int j = 0; j < mainViewDimensions.first - 1; j++) {
		std::cout << std::setw(padding);
		std::cout << ".";
		std::cout << std::setw(padding);
		//This stops the final line from starting another line, since there are no other lines to be made
	}
	std::cout << "  .| " << mainViewDimensions.second;

	drawLine(mainViewDimensions.first, padding, dash, true);
}

void Screen::drawMainView(std::string title, std::string description) {
	int lineNumber = 0;
	bool titleDifferentiator = true; //Used to know whether to draw the title or description later on

	//Finding the boundaries of the alert box (Middle of the main Screen)
	int topBoundary = (mainViewDimensions.second / 2) - ((alertViewDimensions.second / 2) - 1); //We add or minus 1 to the calculation to allow room for the horizontal lines
	int bottomBoundary = topBoundary + ((alertViewDimensions.second / 2) - 1);
	int leftBoundary = (mainViewDimensions.first / 2) - (alertViewDimensions.first / 2);
	int rightBoundary = mainViewDimensions.first - leftBoundary - alertViewDimensions.first;

	std::cout << "\n";
	drawLine(mainViewDimensions.first, padding, number, false);
	drawLine(mainViewDimensions.first, padding, dash, true);

	std::cout << "|";
	for (int i = 0; i < mainViewDimensions.second - 1; i++) {
		//Regular screen drawing
		if (lineNumber < topBoundary || lineNumber > bottomBoundary) {
			for (int j = 0; j < mainViewDimensions.first - 1; j++) {
				std::cout << std::setw(padding);
				std::cout << ".";
				std::cout << std::setw(padding);
			}
			std::cout << "  .| " << i + 1;
			std::cout << "\n|";
			
			lineNumber++;
		}
		//If we have reached the boundaries for where the alert should go
		else {
			//Inside the top and bottom lines
			if (lineNumber != topBoundary && lineNumber != bottomBoundary) {

				//Left side
				for (int j = 0; j < leftBoundary - 1; j++) {
					std::cout << std::setw(padding);
					std::cout << "/";
					std::cout << std::setw(padding);
				}

				//Alert content
				std::cout << "|";
				if (titleDifferentiator) {
					std::cout << title << std::setw((alertViewDimensions.first * padding) - title.length()) << "|";
					titleDifferentiator = false;
				}
				else {
					std::cout << description << std::setw((alertViewDimensions.first * padding) - description.length()) << "|";
				}

				//Right side
				for (int j = 0; j < rightBoundary - 1; j++) {
					std::cout << std::setw(padding);
					std::cout << "/";
					std::cout << std::setw(padding);
				}

				std::cout << "  /| " << i + 1;
				std::cout << "\n|";

				lineNumber++;
			}
			else { //Top and bottom
				//Left side
				for (int j = 0; j < leftBoundary; j++) {
					std::cout << std::setw(padding);
					std::cout << "/";
				}

				//Horizontal lines
				drawLine(alertViewDimensions.first, padding, dash, false);

				//Right side
				for (int j = 0; j < rightBoundary - 1; j++) {
					std::cout << std::setw(padding);
					std::cout << "/";
				}

				std::cout << "  /| " << i + 1;
				std::cout << "\n|";

				lineNumber++;
			}
		}
	}

	//Final line
	for (int j = 0; j < mainViewDimensions.first - 1; j++) {
		std::cout << std::setw(padding);
		std::cout << ".";
		std::cout << std::setw(padding);
	}
	std::cout << "  .| " << mainViewDimensions.second;

	drawLine(mainViewDimensions.first, padding, dash, true);
}

//---------------------------------------------------------------------------------------------------------------------------------

//Input Screen---------------------------------------------------------------------------------------------------------------------
//Should this be changed to a simple ">>>"? If not I'll have to make an input handler myself to make input appear inside the box...
void Screen::drawInputView() {
	drawLine(inputViewDimensions.first, padding, dash, true);
	std::cout << "|Input: " << std::setw((inputViewDimensions.first * padding) - 7) << "|";
	drawLine(inputViewDimensions.first, padding, dash, true);
}

void Screen::drawInputView(std::string description) {
	drawLine(inputViewDimensions.first, padding, dash, true);
	std::cout << "|";
	std::cout << description << std::setw((inputViewDimensions.first * padding) - description.length()) << "|";
	drawLine(inputViewDimensions.first, padding, dash, true);
}

//---------------------------------------------------------------------------------------------------------------------------------

void Screen::drawScreen() {
	system("CLS"); // Clear screen

	//The views can be re-arranged to liking
	drawCommandView(tool);
	drawMainView("Resizing will delete your", "existing image. Continue?");
	drawInputView("Temporary box?");

	std::cout << "Input >>> ";
}