#include "../include/tools.hpp"

#include <iostream>


Tool::Tool() {}
Tool::~Tool() {}

void Tool::fillSquare(const int xCoord, const int yCoord, File*& currentFile, consoleColour colour) {
    currentFile->pixels[(xCoord - 1) + ((yCoord - 1) * currentFile->width)] = colour;
}

void Tool::fillSquare(const std::vector<std::pair<int, int>>& coords, File*& currentFile, consoleColour colour) {
    for (int i = 0; i < coords.size(); i++) {
        currentFile->pixels[(coords[i].first - 1) + ((coords[i].second - 1) * currentFile->width)] = colour;
    }
}

void Tool::fillTool(const int xCoord, const int yCoord, File*& currentFile, consoleColour colour) {
    std::unordered_set<std::pair<int, int>, pair_hash> checkedTiles;
    std::vector<std::pair<int, int>> finalisedListOfTiles;

    consoleColour firstTileColour = currentFile->pixels[(xCoord - 1) + ((yCoord - 1) * currentFile->width)];

    checkSurroundingTiles(xCoord, yCoord, currentFile, firstTileColour, checkedTiles);

    for (auto pair : checkedTiles) {
        finalisedListOfTiles.emplace_back(pair.first, pair.second);
    }

    fillSquare(finalisedListOfTiles, currentFile, colour);
}


void Tool::checkSurroundingTiles(const int xCoord, const int yCoord, File*& currentFile, consoleColour firstTileColour, std::unordered_set<std::pair<int, int>, pair_hash>& setToAddTo) {
    setToAddTo.insert(std::make_pair(xCoord, yCoord));

    // Above -> If the tile above is not outside the file, and the colour is the same
    if (yCoord - 1 >= 1 && currentFile->pixels[(xCoord - 1) + ((yCoord - 2) * currentFile->width)] == firstTileColour) {
        // If the tile is not in the set of tiles already, call checkSurroundingTiles again
        if (setToAddTo.find(std::make_pair(xCoord, yCoord - 1)) == setToAddTo.end()) {
            // This will add the tile to the checkedTiles set, and perform the same checks to surrounding tiles
            checkSurroundingTiles(xCoord, yCoord - 1, currentFile, firstTileColour, setToAddTo);
        }
    }

    // Left
    if (xCoord - 1 >= 1 && currentFile->pixels[(xCoord - 2) + ((yCoord - 1) * currentFile->width)] == firstTileColour) {
        if (setToAddTo.find(std::make_pair(xCoord - 1, yCoord)) == setToAddTo.end()) {
            checkSurroundingTiles(xCoord - 1, yCoord, currentFile, firstTileColour, setToAddTo);
        }
    }

    // Right
    if (xCoord + 1 <= currentFile->width && currentFile->pixels[(xCoord)+((yCoord - 1) * currentFile->width)] == firstTileColour) {
        if (setToAddTo.find(std::make_pair(xCoord + 1, yCoord)) == setToAddTo.end()) {
            checkSurroundingTiles(xCoord + 1, yCoord, currentFile, firstTileColour, setToAddTo);
        }
    }

    // Below
    if (yCoord + 1 <= currentFile->height && currentFile->pixels[(xCoord - 1) + ((yCoord)*currentFile->width)] == firstTileColour) {
        if (setToAddTo.find(std::make_pair(xCoord, yCoord + 1)) == setToAddTo.end()) {
            checkSurroundingTiles(xCoord, yCoord + 1, currentFile, firstTileColour, setToAddTo);
        }
    }
}

//Bresenham's line algorithm
void Tool::lineTool(const std::pair<int, int> startCoords, const std::pair<int, int> endCoords, File*& currentFile, consoleColour colour) {
    std::vector<std::pair<int, int>> finalCoordsToFill;
    
    int x1 = startCoords.first;
    int y1 = startCoords.second;
    
    int x2 = endCoords.first;
    int y2 = endCoords.second;
    
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    
    int err = dx - dy;
    
    while (true) {
        finalCoordsToFill.emplace_back(std::make_pair(x1, y1));
    
        if (x1 == x2 && y1 == y2) break;
    
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
    
    fillSquare(finalCoordsToFill, currentFile, colour);
}