#ifndef ENUMS
#define ENUMS

#include <Windows.h>

enum consoleColour {
	//For use in SetConsoleAttribute()
	red = FOREGROUND_RED | BACKGROUND_RED,
	yellow = FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_GREEN,
	green = FOREGROUND_GREEN | BACKGROUND_GREEN,
	blue = FOREGROUND_BLUE | BACKGROUND_BLUE,
	white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	black = 0
};

enum lineType {
	//For readability
	dash,
	number
};

enum commandScreenType {
	//For readability
	root,
	file,
	tool,
	colour
};


#endif
