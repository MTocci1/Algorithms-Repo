#include <iostream>
#include <fstream>
#include <string>
#include <list>
// Include for std::random_device
#include <random>

using namespace std;


// Define a Node class for the binary tree
class Node {
public:
    string data;
    Node* left;
    Node* right;

    Node(string item) : data(item), left(nullptr), right(nullptr) {}
};

// Function to insert a node into the BST and print the path
Node* insert(Node* root, string item) {
    if (root == nullptr) {
        return new Node(item);
    }

    if (item < root->data) {
        cout << "L, ";
        root->left = insert(root->left, item);
    }
    else if (item > root->data) {
        cout << "R, ";
        root->right = insert(root->right, item);
    }

    return root;
}

// Function to perform an in-order traversal of the BST and print its content
void inOrderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    inOrderTraversal(root->left);
    cout << root->data << endl;
    inOrderTraversal(root->right);
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

    Node* root = nullptr;

    int index = 0;
    string line;
    while (getline(file, line)) {
        cout << "Inserting " << line << " Path: ";
        root = insert(root, line);
        cout << endl;
        index++;
    }

    file.close();

    cout << endl << "BST In-Order Traversal: " << endl;
    inOrderTraversal(root);
    cout << endl;

    return 0;
}