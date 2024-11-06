#include <iostream>
#include <iomanip>
#include "../include/screen.hpp"

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
	std::cout << "\n";
	std::cout << "|Example, example, example";
	drawLine(commandViewDimensions.first, padding, dash);
}

void screen::drawScreen() {
	drawCommandView();
}