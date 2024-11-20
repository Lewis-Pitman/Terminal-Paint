#include <iostream>
#include <Windows.h>

#include "../include/screen.hpp"

int temp{ 0 };

int main() {
	File defaultFile = File(20, 20);

	Screen* pScreen = new Screen(defaultFile);
	pScreen->drawScreen();

	std::cin >> temp;

	pScreen->resizeMainView(); //Testing the resize function with invalid parameters
	pScreen->drawScreen();

	std::cin >> temp;
}