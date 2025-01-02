#include <fstream> //Combo of ofstream and ifstream -> Reads and writes to files
#include <cstdint>
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

void File::openFile() {
    File* currentFile = this;
    std::ifstream file("C:/Users/Lewis/Desktop/TPAINT_Files/open.TPAINT"); //Test directory, will be changed in final build
    std::string line;
    consoleColour* newPixels = nullptr;
    int lineNumber = 0;

    int width = 0;
    int height = 0;

    if (file.is_open()) {
        try {
            while (std::getline(file, line)) {
                if (lineNumber == 0) {
                    width = std::stoi(line);
                    lineNumber++;
                }
                else if (lineNumber == 1) {
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
        catch (const std::exception& e) {
            //--- error message
        }
    }
    else {
        //--- error message
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
        //--- error message
    }
}

void File::exportFile() {
    //Exports the created image to a BMP

    std::ofstream file("C:/Users/Lewis/Desktop/bmptest/image.bmp", std::ios::binary);

    //Calculate the size of one row (width * 3 for RGB)
    std::uint32_t rowSize = width * 3;

    //Ensure each row is a multiple of 4 bytes (padding)
    if (rowSize % 4 != 0) {
        rowSize += 4 - (rowSize % 4);
    }

    std::uint32_t pixelDataSize = rowSize * height;

    std::uint32_t fileSize = 14 + 40 + pixelDataSize; //14 for the header, 40 for the info header, pixelDataSize for the pixel data

    //Convert fileSize to little-endian format
    unsigned char convertedFileSize[4] = {
        fileSize & 0xFF,            //Least significant byte
        (fileSize >> 8) & 0xFF,     //Second byte
        (fileSize >> 16) & 0xFF,    //Third byte
        (fileSize >> 24) & 0xFF     //Most significant byte
    };

    //BMP Header
    unsigned char header[14] = {
        0x42, 0x4D,                    //"BM" signature
        convertedFileSize[0], convertedFileSize[1], convertedFileSize[2], convertedFileSize[3],  //File size
        0x00, 0x00, 0x00, 0x00,        //Reserved (set to 0)
        0x36, 0x00, 0x00, 0x00         //Pixel data offset (54 bytes)
    };

    //BMP Info Header (DIB header)
    unsigned char bitMapInfoHeader[40] = {
        0x28, 0x00, 0x00, 0x00,       // DIB header size (40 bytes)
        width & 0xFF, (width >> 8) & 0xFF, (width >> 16) & 0xFF, (width >> 24) & 0xFF,  //Width (little-endian)
        height & 0xFF, (height >> 8) & 0xFF, (height >> 16) & 0xFF, (height >> 24) & 0xFF, //Height (little-endian)
        0x01, 0x00,                   // Color planes (must be 1)
        0x18, 0x00,                   // BitCount (24 bits, 3 bytes per pixel)
        0x00, 0x00, 0x00, 0x00,       // Compression (0 = no compression)
        pixelDataSize & 0xFF, (pixelDataSize >> 8) & 0xFF, (pixelDataSize >> 16) & 0xFF, (pixelDataSize >> 24) & 0xFF, // Image Size
        0x00, 0x00, 0x00, 0x00,       // X pixels per meter (0)
        0x00, 0x00, 0x00, 0x00,       // Y pixels per meter (0)
        0x00, 0x00, 0x00, 0x00,       // Colors in Color Table (0 for 24-bit)
        0x00, 0x00, 0x00, 0x00        // Important Colors (0)
    };

    unsigned char* pixelData = new unsigned char[width * height * 3];

    //BMP starts from bottom left and draws upwards.
    for (int i = 0; i < width * height; i++) { 
        switch (pixels[i]) {
        case red:
            pixelData[i * 3] = 0x00; //Blue
            pixelData[i * 3 + 1] = 0x00; //Green
            pixelData[i * 3 + 2] = 0xFF; //Red
            break;
        case yellow:
            pixelData[i * 3] = 0x00;  
            pixelData[i * 3 + 1] = 0xFF;
            pixelData[i * 3 + 2] = 0xFF;
            break;
        case green:
            pixelData[i * 3] = 0x00;
            pixelData[i * 3 + 1] = 0xFF;
            pixelData[i * 3 + 2] = 0x00;
            break;
        case blue:
            pixelData[i * 3] = 0xFF;
            pixelData[i * 3 + 1] = 0x00;
            pixelData[i * 3 + 2] = 0x00;
            break;
        case white:
            pixelData[i * 3] = 0xFF;
            pixelData[i * 3 + 1] = 0xFF;
            pixelData[i * 3 + 2] = 0xFF;
            break;
        default:
            pixelData[i * 3] = 0x00;
            pixelData[i * 3 + 1] = 0x00;
            pixelData[i * 3 + 2] = 0x00;
            break;
        }
    }

    if (file.is_open()) {
        //BMP header
        file.write(reinterpret_cast<char*>(header), sizeof(header)); //Reinterpret_cast casts by memory only, regardless of data type. "Dangerous casting"

        //DIB header
        file.write(reinterpret_cast<char*>(bitMapInfoHeader), sizeof(bitMapInfoHeader));

        //Pixel data (with padding)
        for (int y = height - 1; y >= 0; --y) {
            file.write(reinterpret_cast<char*>(&pixelData[y * width * 3]), width * 3);

            //If row size isn't a multiple of 4, write padding bytes
            if (rowSize > width * 3) {
                unsigned char padding[3] = { 0x00, 0x00, 0x00 }; // 3 bytes of padding
                file.write(reinterpret_cast<char*>(padding), rowSize - width * 3);
            }
        }

        file.close();
    }
    else {
        throw std::runtime_error("Error opening file");
    }
}