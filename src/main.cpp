#include <iostream>

#include "../include/screen.hpp"

int temp{ 0 };

int main() {
	Screen* pScreen = new Screen(20, 20);
	pScreen->drawScreen();

	std::cin >> temp;
	
	pScreen->resizeMainView();
	pScreen->drawScreen();

	std::cin >> temp;

}