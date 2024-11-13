#include <iostream>
#include <iomanip>
#include <array>
#include <Windows.h>

#include "../include/screen.hpp"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

screen::screen() { //constructor
	static std::vector<consoleColour> pixels;
	pixels.reserve(50 * 50); //Reserve the memory needed for the maximum size.
}

screen::~screen() {} //Deconstructor

inline void screen::drawLine(int width, int padding, lineType type) {
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

inline void screen::printCommands(commandScreenType type) { 

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

inline void screen::drawCommandView(commandScreenType type) {
	drawLine(commandViewDimensions.first, padding, dash);
	std::cout << "|Available commands:" << std::setw((commandViewDimensions.first * padding) - 19) << "|";
	std::cout << "\n|";
	printCommands(type);
	drawLine(commandViewDimensions.first, padding, dash);
}

inline void screen::drawCommandView(std::string title, std::string description) { //Overload for a custom title and description
	drawLine(commandViewDimensions.first, padding, dash);
	std::cout << "|";
	std::cout << title << std::setw((commandViewDimensions.first * padding) - title.length()) << "|";
	std::cout << "\n|";
	std::cout << description << std::setw((commandViewDimensions.first * padding) - description.length()) << "|";
	drawLine(commandViewDimensions.first, padding, dash);
}

void screen::drawMainView() {
	drawLine(mainViewDimensions.first, padding, number);
	drawLine(mainViewDimensions.first, padding, dash);

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
	for (int j = 0; j < mainViewDimensions.first - 1; j++) {
		std::cout << std::setw(padding);
		std::cout << ".";
		std::cout << std::setw(padding);
		//This stops the final line from starting another line, since there are no other lines to be made
	}
	std::cout << "  .| " << mainViewDimensions.second;

	drawLine(mainViewDimensions.first, padding, dash);
}

void screen::drawMainView(std::string title, std::string description) {
	/*TODO------------------------------
	have either a seperate function or do it within this function itself:
	check the line number each time a line is drawn
	
	Get the height of the alert box, divide by 2 and add/subtract it to mainViewDimensions.second / 2 to find the line numbers needed. 
	So if the height of the main screen was 20, the top of the alert box is line 9 and the bottom is line 11.
	Should be fairly simple to get content displaying inside the box once created
	*/

	int lineNumber = 0;

	drawLine(mainViewDimensions.first, padding, number);
	drawLine(mainViewDimensions.first, padding, dash);

	std::cout << "|";
	for (int i = 0; i < mainViewDimensions.second - 1; i++) {
		for (int j = 0; j < mainViewDimensions.first - 1; j++) {
			std::cout << std::setw(padding);
			std::cout << ".";
			std::cout << std::setw(padding);
		}
		std::cout << "  .| " << i + 1;
		std::cout << "\n|";

		lineNumber++;
	}
	for (int j = 0; j < mainViewDimensions.first - 1; j++) {
		std::cout << std::setw(padding);
		std::cout << ".";
		std::cout << std::setw(padding);
	}
	std::cout << "  .| " << mainViewDimensions.second;

	drawLine(mainViewDimensions.first, padding, dash);
}

void screen::drawInputView() {
	drawLine(inputViewDimensions.first, padding, dash);
	std::cout << "|Input: " << std::setw((inputViewDimensions.first * padding) - 7) << "|";
	drawLine(inputViewDimensions.first, padding, dash);
}

void screen::drawInputView(std::string description) {
	drawLine(inputViewDimensions.first, padding, dash);
	std::cout << "|";
	std::cout << description << std::setw((inputViewDimensions.first * padding) - description.length()) << "|";
	drawLine(inputViewDimensions.first, padding, dash);
}

void screen::drawScreen() {
	drawCommandView(tool);
	drawInputView("Enter a command: ");
	drawMainView();
}