#include <iostream>
#include <fstream>
#include <string>
// Include for std::random_device
#include <random>

using namespace std;

// Function to merge two sorted subarrays
void merge(string* arr, int left, int mid, int right, int& comparisons) {
    // Calculate the sizes of the subarrays
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    // Create temporary arrays for the subarrays
    string* leftArray = new string[sizeLeft];
    string* rightArray = new string[sizeRight];

    // Copy data to temporary arrays
    for (int i = 0; i < sizeLeft; ++i) {
        leftArray[i] = arr[left + i];
    }
    for (int i = 0; i < sizeRight; ++i) {
        rightArray[i] = arr[mid + 1 + i];
    }

    // Merge the two subarrays back into array
    // Index for the left subarray
    int i = 0;
    // Index for the right subarray
    int j = 0;
    // Index for the merged array
    int k = left;

    while (i < sizeLeft && j < sizeRight) {
        // Convert characters to lowercase for case-insensitive comparison
        for (char& ch : leftArray[i]) {
            ch = tolower(ch);
        }
        for (char& ch : rightArray[j]) {
            ch = tolower(ch);
        }

        comparisons++;
        // Compare and merge based on lowercase strings
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            ++i;
        }
        else {
            arr[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    // Copy the remaining elements of leftArray[], if any
    while (i < sizeLeft) {
        arr[k] = leftArray[i];
        ++i;
        ++k;
    }

    // Copy the remaining elements of rightArray[], if any
    while (j < sizeRight) {
        arr[k] = rightArray[j];
        ++j;
        ++k;
    }

    // Delete temporary arrays
    delete[] leftArray;
    delete[] rightArray;
}

// Merge sort 
void mergeSort(string* arr, int left, int right, int& comparisons) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Recursively sort the first and second halves
        mergeSort(arr, left, mid, comparisons);
        mergeSort(arr, mid + 1, right, comparisons);

        // Merge the sorted halves
        merge(arr, left, mid, right, comparisons);
    }
}

// Linear search
int linearSearch(string* arr, int size, string targetItem, int& linearComparisons) {
    for (int i = 0; i < size; i++) {
        linearComparisons++;
        if (arr[i] == targetItem) {
            cout << "Found " << targetItem << " at index " << i << endl;
            // Return the index of the item
            return i;
        }
    }
    return -1;
}

// Binary search
int binarySearch(string* arr, int size, string targetItem, int& binaryComparisons) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Convert to lowercase
        string midItem = arr[mid];

        binaryComparisons++;

        if (midItem == targetItem) {
            // Return the index of the item
            cout << "Found " << targetItem << " at index " << mid << endl;
            return mid;
        }
        else if (midItem < targetItem) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}



int main() {

    // Read all lines of magicitems.txt and put them in an array
    // Open the magicitems.txt file
    ifstream file("magicitems.txt");

    // Handle failure
    if (!file)
    {
        cerr << "Failed to open magicitems.txt" << endl;
        return 1;
    }

    // Count the number of lines in the file
    int magicItemsSize = 0;
    string line;
    while (getline(file, line))
    {
        magicItemsSize++;
    }

    // Close and reopen the file to read from the beginning
    file.close();
    file.open("magicitems.txt");

    // Create a dynamically allocated array
    string* magicItemsArray = new string[magicItemsSize];

    // Read the file line by line and store each line in the array
    int index = 0;
    while (getline(file, line))
    {
        magicItemsArray[index] = line;
        index++;
    }

    // Close the file
    file.close();

    int comparisonsMergeSort = 0;
    // Sort the strings using merge sort
    mergeSort(magicItemsArray, 0, magicItemsSize - 1, comparisonsMergeSort);

    // Set up randomizer
    random_device rd;
    srand(rd());

    // Search
    int totalComparisonsLinear = 0;
    int totalComparisonsBinary = 0;

    for (int i = 0; i < 42; i++) {
        // Generate a random index between 0 and the size of the array
        int index = rand() % (magicItemsSize);

        int linearComparisons = 0;
        int binaryComparisons = 0;

        string targetItem = magicItemsArray[index]; 

        linearSearch(magicItemsArray, magicItemsSize, targetItem, linearComparisons);
        binarySearch(magicItemsArray, magicItemsSize, targetItem, binaryComparisons);

        totalComparisonsLinear += linearComparisons;
        totalComparisonsBinary += binaryComparisons;

        cout << "Search " << (i + 1) << " linear comparisons: " << linearComparisons << "\n";
        cout << "Search " << (i + 1) << " binary comparisons: " << binaryComparisons << "\n" << endl;
    }

    // Convert totalComparisons to a double and divide by 42 for average
    double averageComparisonsLinear = static_cast<double>(totalComparisonsLinear) / 42;
    printf("Average comparisons for linear search: %.2f\n", averageComparisonsLinear); 

    // Convert totalComparisons to a double and divide by 42 for average
    double averageComparisonsBinary = static_cast<double>(totalComparisonsBinary) / 42;
    printf("Average comparisons for binary search: %.2f\n", averageComparisonsBinary);

    // Delete dynamically allocated memory
    delete[] magicItemsArray;

	return 0;
}