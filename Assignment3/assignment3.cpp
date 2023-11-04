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

// In-order traversal function
void inOrderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    inOrderTraversal(root->left);
    cout << root->data << endl;
    inOrderTraversal(root->right);
}

// Function to look up an item in the BST and print the path
bool lookup(Node* root, string item, int& comparisons, string& path) {
    if (root == nullptr) {
        return false;
    }

    comparisons++; // Increment comparisons for each level
    if (item == root->data) {
        return true;
    }
    else if (item < root->data) {
        path += "L, ";
        return lookup(root->left, item, comparisons, path);
    }
    else {
        path += "R, ";
        return lookup(root->right, item, comparisons, path);
    }
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

    // Read magicitems-find-in-bst.txt and look up each item in the BST
    ifstream lookupFile("magicitems-find-in-bst.txt");

    if (!lookupFile) {
        cerr << "Failed to open magicitems-find-in-bst.txt" << endl;
        return 1;
    }

    int totalComparisons = 0;
    int totalLookups = 0;

    while (getline(lookupFile, line)) {
        int comparisons = 0;
        string path = "";
        bool found = lookup(root, line, comparisons, path);
        totalLookups++;
        totalComparisons += comparisons;
        if (found) {
            cout << "Item found: " << line << endl << "Path: " << path << endl << "Comparisons: " << comparisons << endl << endl;
        } else {
            cout << "Item not found" << endl;
        }
    }

    lookupFile.close();
    double averageComparisons = static_cast<double>(totalComparisons) / totalLookups;
    printf("Average comparisons: %.2f\n", averageComparisons);

    return 0;
}