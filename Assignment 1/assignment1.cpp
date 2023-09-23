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
void selectionSort(string* arr, int size) {
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


    cout << "Palindromes: " << endl;
    // Check each line in the array for palindromes and print it if it is
    for (int i = 0; i < magicItemsSize; ++i) {
        if (isPalindrome(magicItemsArray[i])) {
            cout << magicItemsArray[i] << endl;
        }
    }

    // Shuffle before sorting
    shuffle(magicItemsArray, magicItemsSize);

    // Sort magicItemsArray using selection sort
    selectionSort(magicItemsArray, magicItemsSize);

    cout << "\nSorted Magic Items:" << endl;
    for (int i = 0; i < magicItemsSize; ++i) {
        cout << magicItemsArray[i] << endl;
    }

    // Delete dynamically allocated memory
    delete[] magicItemsArray;

    return 0;
}
