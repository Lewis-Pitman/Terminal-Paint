#include <fstream> //Combo of ofstream and ifstream -> Reads and writes to files
#include <string>

#include "../include/file.hpp"
#include "../include/enums.hpp"

File::File(int fileWidth, int fileHeight) : width(fileWidth), height(fileHeight) {
    pixels = new consoleColour[fileWidth * fileHeight];

    int temp;

    for (int i = 0; i < fileWidth * fileHeight; i++) {
        pixels[i] = black;
    }
}

File::File(int fileWidth, int fileHeight, consoleColour* openedFilePixels) : width(fileWidth), height(fileHeight) {
    pixels = openedFilePixels;
}

File::~File() {
    delete[] pixels;
}

void File::openFile(File*& currentFile) {
    std::ifstream file("C:/Users/Lewis/Desktop/TPAINT_Files/open.TPAINT"); //Test directory, will be changed in final build
    std::string line;
    consoleColour* newPixels = nullptr;
    int lineNumber = 0;

    int width = 0;
    int height = 0;

    if (file.is_open()) {

        while (std::getline(file, line)) { 
            if (lineNumber == 0) {
                width = std::stoi(line);
                lineNumber++;
            }
            else if (lineNumber == 1){
                height = std::stoi(line);
                newPixels = new consoleColour[width * height];
                lineNumber++;
            }
            else {

                newPixels[lineNumber - 2] = consoleColour(std::stoi(line));

                lineNumber++;
            }
        }

        File* newFile = new File(width, height, newPixels);
        delete currentFile;
        currentFile = newFile;

    }
    else {
        //--- error
    }
}

void File::saveFile() {
    std::ofstream file("C:/Users/Lewis/Desktop/TPAINT_Files/test.TPAINT"); //Test directory, will be changed in final build

    if (file.is_open()) {
        //Header containing width and height
        file << width << "\n" << height << "\n";

        //Writing actual data
        for (int i = 0; i < width * height; i++) {
            file << pixels[i];
            file << '\n';
        }

        file.close();
    }
    else {
        //Display an alert to say there was an error??
    }
}