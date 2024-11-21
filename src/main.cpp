#include <iostream>
#include <Windows.h>

#include "../include/screen.hpp"

int temp{ 0 };

int main() {
	File* defaultFile = new File(20, 20);

	Screen* pScreen = new Screen(defaultFile);
	pScreen->drawScreen();

	std::cin >> temp;


	defaultFile->openFile(defaultFile);

	pScreen->resizeMainView();
	pScreen->drawScreen();

	std::cin >> temp;
}