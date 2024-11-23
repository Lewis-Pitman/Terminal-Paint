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


	/*Testing file functionality
	defaultFile->openFile(defaultFile);
	delete pScreen;
	pScreen = new Screen(defaultFile);
	
	pScreen->drawScreen();

	std::cin >> temp;
	*/

	//Testing tool functionality
	currentTool.fillSquare(5, 5, defaultFile, red);
	currentTool.fillSquare(6, 5, defaultFile, red);
	currentTool.fillSquare(7, 5, defaultFile, red);
	currentTool.fillSquare(8, 5, defaultFile, red);
	currentTool.fillSquare(8, 6, defaultFile, red);
	currentTool.fillSquare(8, 7, defaultFile, red);
	currentTool.fillSquare(8, 8, defaultFile, red);
	currentTool.fillSquare(7, 8, defaultFile, red);
	currentTool.fillSquare(6, 8, defaultFile, red);
	currentTool.fillSquare(5, 8, defaultFile, red);
	currentTool.fillSquare(5, 7, defaultFile, red);
	currentTool.fillSquare(5, 6, defaultFile, red);
	currentTool.fillSquare(5, 5, defaultFile, red);
	
	
	pScreen->drawScreen();
	std::cin >> temp;


	currentTool.fillTool(10, 10, defaultFile, blue);
	pScreen->drawScreen();
	std::cin >> temp;

	currentTool.fillTool(6, 6, defaultFile, green);
	pScreen->drawScreen();
	std::cin >> temp;

	currentTool.fillTool(5, 5, defaultFile, yellow);
	pScreen->drawScreen();
	std::cin >> temp;
	
}