#include <iostream>
#include <fstream>
#include <string>
// Include for std::random_device
#include <random>

using namespace std;

// Define a Node class for the stack and queue
class Node {
public:
    char data;
    Node* next;

    Node(char value) : data(value), next(nullptr) {}
};

// Create a stack using the Node class
class Stack {
private:
    // Point to the top of the stack
    Node* top;

public:
    Stack() : top(nullptr) {}

    // Push a value onto the stack
    void push(char value) {
        Node* newNode = new Node(value);
        newNode -> next = top;
        top = newNode;
    }

    // Pop the top value from the stack
    char pop() {
        if (isEmpty()) {
            cerr << "Stack is empty." << endl;
            return -1;
        }
        char value = top->data;
        Node* temp = top;
        top = top -> next;
        delete temp;
        return value;
    }

    // Check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }
};

// Create a queue using the Node class
class Queue {
private:
    Node* front;
    Node* back;

public:
    Queue() : front(nullptr), back(nullptr) {}

    // Enqueue a value into the queue
    void enqueue(char value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = back = newNode;
        }
        else {
            back -> next = newNode;
            back = newNode;
        }
    }

    // Dequeue a value from the queue
    char dequeue() {
        if (isEmpty()) {
            cerr << "Queue is empty." << endl;
            return -1;
        }
        char value = front->data;
        Node* temp = front;
        front = front -> next;
        delete temp;
        return value;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }
};

// Check if a string is a palindrome (ignoring spaces and capitalization)
bool isPalindrome(const string& str) {
    Stack stack;
    Queue queue;

    // Push characters to the stack and queue (ignoring spaces and converting to lowercase)
    for (char i : str) {
        if (!isspace(i)) {
            stack.push(tolower(i));
            queue.enqueue(tolower(i));
        }
    }

    // Compare characters from the stack and queue
    while (!stack.isEmpty() && !queue.isEmpty()) {
        if (stack.pop() != queue.dequeue()) {
            // Not a palindrome
            return false;
        }
    }

    return true;
}

// Shuffle the array using the Knuth shuffle algorithm with std::random_device seeding
void shuffle(string* arr, int size) {
    random_device rd;
    srand(rd());

    for (int i = size - 1; i > 0; --i) {
        // Generate a random index between 0 and i
        int j = rand() % (i + 1); 
        // Swap elements at i and j
        swap(arr[i], arr[j]);     
    }
}

// Selection sort 
void selectionSort(string* arr, int size, int& comparisons) {
    for (int i = 0; i < size - 1; ++i) {
        int index = i;
        for (int j = i + 1; j < size; ++j) {
            // Convert both strings to lowercase for comparison
            for (char& ch : arr[j]) {
                ch = tolower(ch);
            }
            for (char& ch : arr[index]) {
                ch = tolower(ch);
            }
            comparisons++;
            // Compare the lowercase strings
            if (arr[j] < arr[index]) {
                index = j;
            }
        }
        // If a smaller element was found, swap it with the current element
        if (index != i) {
            swap(arr[i], arr[index]);
        }
    }
}

// Insertion sort
void insertionSort(string* arr, int size, int& comparisons) {
    for (int i = 1; i < size; ++i) {
        int j = i;
        while (j > 0) {
            // Convert both strings to lowercase for comparison
            for (char& ch : arr[j]) {
                ch = tolower(ch);
            }
            for (char& ch : arr[j - 1]) {
                ch = tolower(ch);
            }
            comparisons++;
            // Compare the lowercase strings
            if (arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
                --j;
            }
            else {
                break;
            }
        }
    }
}

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

int main() {
    // Test the stack
    Stack testStack;
    testStack.push('A');
    testStack.push('B');
    testStack.push('C');

    cout << "Stack contents: ";
    while (!testStack.isEmpty()) {
        cout << testStack.pop() << " ";
    }
    cout << endl;

    // Test the queue
    Queue testQueue;
    testQueue.enqueue('A');
    testQueue.enqueue('B');
    testQueue.enqueue('C');

    cout << "Queue contents: ";
    while (!testQueue.isEmpty()) {
        cout << testQueue.dequeue() << " ";
    }
    cout << endl;

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


    cout << "\nPalindromes: " << endl;
    // Check each line in the array for palindromes and print it if it is
    for (int i = 0; i < magicItemsSize; ++i) {
        if (isPalindrome(magicItemsArray[i])) {
            cout << magicItemsArray[i] << endl;
        }
    }

    // Shuffle before sorting
    shuffle(magicItemsArray, magicItemsSize);

    int comparisonsSelectionSort = 0;
    // Sort magicItemsArray using selection sort
    selectionSort(magicItemsArray, magicItemsSize, comparisonsSelectionSort);

    cout << "\nSorted Magic Items (Selection Sort):" << endl;
    for (int i = 0; i < magicItemsSize; ++i) {
        cout << magicItemsArray[i] << endl;
    }
    cout << "Comparisons in Selection Sort: " << comparisonsSelectionSort << endl;

    // Shuffle before sorting again
    shuffle(magicItemsArray, magicItemsSize);

    int comparisonsInsertionSort = 0;
    // Sort magicItemsArray using selection sort
    insertionSort(magicItemsArray, magicItemsSize, comparisonsInsertionSort);

    cout << "\nSorted Magic Items (Insertion Sort):" << endl;
    for (int i = 0; i < magicItemsSize; ++i) {
        cout << magicItemsArray[i] << endl;
    }
    cout << "Comparisons in Insertion Sort: " << comparisonsInsertionSort << endl;

    // Shuffle before sorting again
    shuffle(magicItemsArray, magicItemsSize);

    int comparisonsMergeSort = 0;
    // Sort the strings using merge sort in a case-insensitive manner
    mergeSort(magicItemsArray, 0, magicItemsSize - 1, comparisonsMergeSort);

    cout << "\nSorted Magic Items (Merge Sort):" << endl;
    for (int i = 0; i < magicItemsSize; ++i) {
        cout << magicItemsArray[i] << endl;
    }
    cout << "Comparisons in Merge Sort: " << comparisonsMergeSort << endl;


    // Delete dynamically allocated memory
    delete[] magicItemsArray;

    return 0;
}
