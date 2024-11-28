#ifndef TOOLS
#define TOOLS

#include <utility>
#include <unordered_set>
#include <vector>

#include "../include/enums.hpp"
#include "../include/file.hpp"

//Custom hash function for std::pair<int, int>, as std::unordered_set (Used for fill tool) doesn't support it
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

class Tool {
public:
    const static int colour {blue};
    static bool erasing;

public:
    Tool();
    ~Tool();

    void fillTool(const int xCoord, const int yCoord, File*& currentFile, consoleColour colour);
    void lineTool(const std::pair<int, int> startCoords, const std::pair<int, int> endCoords, File*& currentFile, consoleColour colour);

public:
    void fillSquare(const int xCoord, const int yCoord, File*& currentFile, consoleColour colour);
private:
    void fillSquare(const std::vector<std::pair<int, int>>& coords, File*& currentFile, consoleColour colour);
    void checkSurroundingTiles(const int xCoord, const int yCoord, File*& currentFile, consoleColour firstTileColour, std::unordered_set<std::pair<int, int>, pair_hash>& checkedTiles);
};

#endif