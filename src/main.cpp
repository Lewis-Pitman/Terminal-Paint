#include <iostream>

#include "../include/screen.hpp"

int temp;

int main() {
	screen screen(20, 20);
	screen.drawScreen();

	std::cin >> temp;
}