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
	int lineNumber = 0;

	drawLine(mainViewDimensions.first, padding, number);
	drawLine(mainViewDimensions.first, padding, dash);

	for (int i = 0; i < mainViewDimensions.second; i++) {
		std::cout << "\n|";
		for (int j = 0; j < mainViewDimensions.first; j++) {
			SetConsoleTextAttribute(hConsole, white);
			//SetConsoleTextAttribute(hConsole, pixels[(lineNumber * mainViewDimensions.first) + j]); might work..? Using above for testing purposes
			std::cout << std::setw((padding * 2) - 1);
			std::cout << " ";
		}
		SetConsoleTextAttribute(hConsole, black);
		std::cout << "| " << i + 1;

		lineNumber++;
	}
}

void screen::drawInputView() {
	drawLine(inputViewDimensions.first, padding, dash);
	std::cout << "|Input: " << std::setw((inputViewDimensions.first * padding) - 7) << "|";
	drawLine(inputViewDimensions.first, padding, dash);
}

void screen::drawScreen() {
	drawCommandView(file);
	drawInputView();
	drawMainView();
}