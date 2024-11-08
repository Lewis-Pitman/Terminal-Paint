#include <iostream>
#include <iomanip>
#include <array>
#include "../include/screen.hpp"

//Print an array and return the number of characters used. Necessary for printing boxes
inline int screen::printArray(const char* arrayToPrint) { 
	int count = 0;

	//use pointer
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
	


	drawLine(commandViewDimensions.first, padding, dash);
}

void screen::drawScreen() {
	drawCommandView();
}