#include <iostream>

#include "../include/screen.hpp"

int temp;

int main() {
	screen screen(8, 16);
	screen.drawScreen();

	std::cin >> temp;
}