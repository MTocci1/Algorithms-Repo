#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    // Open the magicitems.txt file
    std::ifstream inputFile("magicitems.txt");

    // Check if file was successfully opened
    if (!inputFile) {
        std::cerr << "Error opening magicitems.txt" << std::endl;
        return 1;
    }

    // Create vector to store the magic items
    std::vector<std::string> magicItems;
    std::string line;

    // Read the file line-by-line
    while (std::getline(inputFile, line)) {
        magicItems.push_back(line);
    }
    // Close the file
    inputFile.close();

    // Print the contents
    for (const std::string& item : magicItems) {
        std::cout << item << std::endl;
    }

    return 0;
}
