#include <iostream>
#include <Windows.h>

#include "../include/screen.hpp"
#include "../include/tools.hpp"

int temp{ 0 };

int main() {
	File* defaultFile = new File(20, 20);

	Tool currentTool;

	Screen* pScreen = new Screen(defaultFile);
	pScreen->drawScreen();

	std::cin >> temp;


	//Testing file functionality
	defaultFile->openFile(defaultFile);
	delete pScreen;
	pScreen = new Screen(defaultFile);
	
	pScreen->drawScreen();

	std::cin >> temp;

	//Testing tool functionality

	currentTool.fillSquare(20, 20, defaultFile, green);
	pScreen->drawScreen();
	std::cin >> temp;

	std::vector<std::pair<int, int>> rectangle;

	//Make a rectangle top right:
    rectangle.push_back(std::make_pair(16, 2));
	rectangle.push_back(std::make_pair(16, 3));
	rectangle.push_back(std::make_pair(16, 4));
	rectangle.push_back(std::make_pair(16, 5));
	rectangle.push_back(std::make_pair(16, 6));
	rectangle.push_back(std::make_pair(17, 6));
	rectangle.push_back(std::make_pair(18, 6));
	rectangle.push_back(std::make_pair(18, 5));
	rectangle.push_back(std::make_pair(18, 4));
	rectangle.push_back(std::make_pair(18, 3));
	rectangle.push_back(std::make_pair(18, 2));
	rectangle.push_back(std::make_pair(17, 2));

	currentTool.fillSquare(rectangle, defaultFile, blue);

	pScreen->drawScreen();

	std::cin >> temp;
	
}