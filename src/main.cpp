#include <iostream>

#include "../include/screen.hpp"

int temp{ 0 };

int main() {
	Screen* pScreen = new Screen(20, 20);
	pScreen->drawScreen();

	std::cin >> temp;

	pScreen->resizeMainView(60, 50, pScreen); //Testing the resize function with invalid parameters
	pScreen->drawScreen();

	std::cin >> temp;

}