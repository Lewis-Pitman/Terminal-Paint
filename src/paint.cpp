#include <string>

#include "../include/paint.hpp"
#include "../include/enums.hpp"

void Paint::Run() {
	while (true){
		
	}
}

void Paint::handleInput(std::string command, commandScreenType availableCommands) {
	switch (availableCommands) {
	case root:

		if (command == "file") {

		}
		else if (command == "tool") {

		}
		else if (command == "colour") {

		}

		break;
	case file:

		if (command == "back") {

		}
		else if (command == "new") {

		}
		else if (command == "open") {

		}
		else if (command == "export") {

		}

		break;
	case tool:

		if (command == "back") {

		}
		else if (command == "brush") {

		}
		else if (command == "line") {

		}
		else if (command == "fill") {

		}
		else if (command == "erase") {

		}

		break;
	case colour:

		if (command == "back") {

		}
		else if (command == "red") {

		}
		else if (command == "yellow") {

		}
		else if (command == "green") {

		}
		else if (command == "blue") {

		}

		break;
	}
}