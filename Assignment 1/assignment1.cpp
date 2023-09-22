#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

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
            std::cerr << "Stack is empty." << std::endl;
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
            std::cerr << "Queue is empty." << std::endl;
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
bool isPalindrome(const std::string& str) {
    Stack stack;
    Queue queue;

    // Push characters to the stack and queue (ignoring spaces and converting to lowercase)
    for (char i : str) {
        if (!std::isspace(i)) {
            stack.push(std::tolower(i));
            queue.enqueue(std::tolower(i));
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


int main() {
    // Test the stack
    Stack testStack;
    testStack.push('A');
    testStack.push('B');
    testStack.push('C');

    std::cout << "Stack contents: ";
    while (!testStack.isEmpty()) {
        std::cout << testStack.pop() << " ";
    }
    std::cout << std::endl;

    // Test the queue
    Queue testQueue;
    testQueue.enqueue('A');
    testQueue.enqueue('B');
    testQueue.enqueue('C');

    std::cout << "Queue contents: ";
    while (!testQueue.isEmpty()) {
        std::cout << testQueue.dequeue() << " ";
    }
    std::cout << std::endl;

    // Read all lines of magicitems.txt and put them in an array
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

    std::cout << "Palindromes: " << std::endl;
    // Check each line in the array for palindromes and print it if it is
    for (int i = 0; i < magicItemsSize; ++i) {
        if (isPalindrome(magicItemsArray[i])) {
            std::cout << magicItemsArray[i] << std::endl;
        }
    }

    // Delete dynamically allocated memory
    delete[] magicItemsArray;

    return 0;
}
