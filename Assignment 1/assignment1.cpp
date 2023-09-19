#include <iostream>
#include <fstream>
#include <string>

// Define a Node class for the stack and queue
class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Create a stack using the Node class
class Stack {
private:
    // Point to the top of the stack
    Node* top;

public:
    Stack() : top(nullptr) {}

    // Push a value onto the stack
    void push(int value) {
        Node* newNode = new Node(value);
        newNode -> next = top;
        top = newNode;
    }

    // Pop the top value from the stack
    int pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty." << std::endl;
            return -1;
        }
        int value = top->data;
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
    void enqueue(int value) {
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
    int dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue is empty." << std::endl;
            return -1;
        }
        int value = front->data;
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


int main() {
    // Test the stack
    Stack myStack;
    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    std::cout << "Stack contents: ";
    while (!myStack.isEmpty()) {
        std::cout << myStack.pop() << " ";
    }
    std::cout << std::endl;

    // Test the queue
    Queue myQueue;
    myQueue.enqueue(1);
    myQueue.enqueue(2);
    myQueue.enqueue(3);

    std::cout << "Queue contents: ";
    while (!myQueue.isEmpty()) {
        std::cout << myQueue.dequeue() << " ";
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

    // Print the magic items:
    for (int i = 0; i < magicItemsSize; ++i) 
    {
        std::cout << magicItemsArray[i] << std::endl;
    }

    // Delete dynamically allocated memory
    delete[] magicItemsArray;

    return 0;
}
