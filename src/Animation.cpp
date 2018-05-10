#include "Animation.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

void Animation::loadFromFile(const std::string& filename)
{
    std::ifstream inFile;
    inFile.open(filename);

    if (!inFile.good())
    {
        throw std::runtime_error("Failed to open animation file: " + filename);
    }

    std::string line;
    std::getline(inFile, line);

    std::stringstream ss(line);

    int numberOfFrames = 0;
    ss >> numberOfFrames;

    for (int i = 0; i < numberOfFrames; ++i)
    {
        sf::IntRect rect;
        std::getline(inFile, line);

        std::stringstream ss2(line);

        int numbers[4];

        for (int j = 0; j < 4; ++j)
        {
            std::string temp;
            std::getline(ss2, temp, ' ');
            std::stringstream ss3(temp);

            ss3 >> numbers[j];
            // std::cout << numbers[j] << "\n";
        }
        rect.left = numbers[0];
        rect.top = numbers[1];
        rect.width = numbers[2];
        rect.height = numbers[3];

        frames.push_back(rect);
    }

    std::getline(inFile, line);
    std::stringstream ss4(line);
    ss4 >> animationTime;

    inFile.close();
}
