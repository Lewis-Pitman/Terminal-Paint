#include <iostream>

#include "../include/screen.hpp"

int temp;

int main() {
	Screen* pScreen = new Screen(20, 20);
	pScreen->drawScreen();

	std::cin >> temp;

	delete pScreen;

	pScreen = new Screen(40, 25);
	pScreen->drawScreen();
}