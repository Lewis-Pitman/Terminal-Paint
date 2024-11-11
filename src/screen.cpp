#include <iostream>
#include <iomanip>
#include <array>
#include "../include/screen.hpp"


extern const std::array<std::string, 3> rootCommands = { "file", "tool", "colour" };
extern const std::array<std::string, 4> fileCommands = { "back", "new", "open", "export" };
extern const std::array<std::string, 4> toolCommands = { "back", "brush", "line", "fill" };
extern const std::array<std::string, 7> colourCommands = { "back", "red", "yellow", "green", "blue", "white", "black" };

//Print an array and return the number of characters used. Necessary for printing boxes
inline int screen::printCommands(commandScreenType type) { 
	switch (type) {
	case root:
		for (int i = 0; i < rootCommands.size() - 1; i++) {
			std::cout << rootCommands[i] << ", ";
		}
		break;
	case file:
		for (int i = 0; i < fileCommands.size() - 1; i++) {
			std::cout << rootCommands[i] << ", ";
		}
		break;
	case tool:
		for (int i = 0; i < toolCommands.size() - 1; i++) {
			std::cout << rootCommands[i] << ", ";
		}
		break;
	case colour:
		for (int i = 0; i < colourCommands.size() - 1; i++) {
			std::cout << rootCommands[i] << ", ";
		}
		break;
	}
	return 0;
}

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
			std::cout << std::setw(padding) << i;
		}
	}
	std::cout << "\n";
}

inline void screen::drawCommandView() {
	drawLine(commandViewDimensions.first, padding, dash);
	std::cout << "|Available commands:" << std::setw((commandViewDimensions.first * padding) - 19) << "|";
	std::cout << "\n|";
	printCommands(tool);


	drawLine(commandViewDimensions.first, padding, dash);
}

void screen::drawScreen() {
	drawCommandView();
}