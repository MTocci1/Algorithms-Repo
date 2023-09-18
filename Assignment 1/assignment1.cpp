#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Open the magicitems.txt file
    std::ifstream file("magicitems.txt");

    // Handle failure
    if (!file) 
    {
        std::cerr << "Failed to open magicitems.txt" << std::endl;
        return 1;
    }

    // Count the number of lines in the file
    int magicItemsSize = 0;
    std::string line;
    while (std::getline(file, line)) 
    {
        magicItemsSize++;
    }

    // Close and reopen the file to read from the beginning
    file.close();
    file.open("magicitems.txt");

    // Create a dynamically allocated array
    std::string* magicItemsArray = new std::string[magicItemsSize];

    // Read the file line by line and store each line in the array
    int index = 0;
    while (std::getline(file, line)) 
    {
        magicItemsArray[index] = line;
        index++;
    }

    // Close the file
    file.close();

    // Print the magic items:
    for (int i = 0; i < magicItemsSize; ++i) 
    {
        std::cout << magicItemsArray[i] << std::endl;
    }

    // Delete dynamically allocated memory
    delete[] magicItemsArray;

    return 0;
}
