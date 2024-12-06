#ifndef PAINT
#define PAINT

#include <string>

class Paint {

public:
	std::string inputtedCommand{ "" };

public:
	Paint();
	~Paint();

	void Run();

private:
	void handleInput(std::string command, commandScreenType availableCommands);
};

#endif
