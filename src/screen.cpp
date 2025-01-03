#include <iostream>
#include <iomanip>
#include <ios>
#include <array>
#include <Windows.h>
#include <stdlib.h>

#include "../include/screen.hpp"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Used for setting colour of the terminal

Screen::Screen(File* file) { //constructor
	mainViewDimensions = { file->width, file->height };

	//Capping the size of the alert box based on the size of the main screen:
	alertViewDimensions.first = (file->width >= 20) ? 10 : file->width / 2;
	alertViewDimensions.second = (file->height >= 20) ? 8 : file->height / 2;

	openedFile = file;
}

Screen::~Screen() {
}

//Misc---------------------------------------------------------------------------------------------------------------------------

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

//---------------------------------------------------------------------------------------------------------------------------------

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
			SetConsoleTextAttribute(hConsole, openedFile->pixels[(j) + (i * (mainViewDimensions.first))]);
			std::cout << std::setw(padding);
			std::cout << "."; //A character needs to be present here to format the box correctly. Using spaces or leaving it blank does not function correctly.
			std::cout << std::setw(padding);
		}
		SetConsoleTextAttribute(hConsole, openedFile->pixels[(mainViewDimensions.first - 1) + (i * mainViewDimensions.first)]);
		std::cout << "  .";
		SetConsoleTextAttribute(hConsole, defaultTerminalColours);
		std::cout << "| " << i + 1;
		std::cout << "\n|";
	}

	//Final line
	for (int j = 0; j < mainViewDimensions.first - 1; j++) {
		SetConsoleTextAttribute(hConsole, openedFile->pixels[(j) + (mainViewDimensions.second * (mainViewDimensions.first - 1))]);
		std::cout << std::setw(padding);
		std::cout << ".";
		std::cout << std::setw(padding);
		//This stops the final line from starting another line, since there are no other lines to be made
	}
	SetConsoleTextAttribute(hConsole, openedFile->pixels[(mainViewDimensions.first - 1) + (mainViewDimensions.second * (mainViewDimensions.first - 1))]);
	std::cout << "  .";
	SetConsoleTextAttribute(hConsole, defaultTerminalColours);
	std::cout << "|" << mainViewDimensions.second;

	drawLine(mainViewDimensions.first, padding, dash, true);
}

//---------------------------------------------------------------------------------------------------------------------------------

//Box -----------------------------------------------------------------------------------------------------------------------------

void Screen::drawBoxView(int width, std::string description) {
		drawLine(width, padding, dash, true);
		std::cout << "|";
		std::cout << description << std::setw((width * padding) - description.length()) << "|";
		drawLine(width, padding, dash, true);
}

//---------------------------------------------------------------------------------------------------------------------------------

void Screen::drawScreen(commandScreenType commandType) {
	system("CLS"); // Clear screen

	//The views can be re-arranged to liking
	drawCommandView(commandType);
	drawMainView();

	std::cout << "Input >>> ";
}

void Screen::drawScreen(std::string message) {
	system("CLS");

	drawBoxView(message.length() / 2, message);
	drawMainView();

	std::cout << "\nInput >>> ";
}