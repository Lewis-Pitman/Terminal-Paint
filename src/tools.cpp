#include "../include/tools.hpp"

#include <queue>

Tool::Tool() {}
Tool::~Tool() {}

void Tool::fillSquare(const int xCoord, const int yCoord, File *&currentFile, consoleColour colour) {
	currentFile->pixels[(xCoord - 1) + ((yCoord - 1) * currentFile->width)] = colour;
}

void Tool::fillSquare(const std::vector<std::pair<int, int>> coords, File *&currentFile, consoleColour colour) {
	for (int i = 0; i < coords.size(); i++) {
		currentFile->pixels[(coords[i].first - 1) + ((coords[i].second - 1) * currentFile->width)] = colour;
	}
}