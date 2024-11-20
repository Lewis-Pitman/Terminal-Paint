#ifndef ENUMS
#define ENUMS

enum consoleColour {
	//For use in SetConsoleAttribute()
	red = 0x40,
	yellow = 0x60,
	green = 0x20,
	blue = 0x10,
	white = 0x70,
	black = 0x00
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
