#include "../include/file.hpp"
#include "../include/enums.hpp"

File::File(int fileWidth, int fileHeight) : width(fileWidth), height(fileHeight) {
    pixels.reserve(fileWidth * fileHeight);
    }