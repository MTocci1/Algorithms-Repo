#include <iostream>
#include <fstream>
#include <string>
#include <list>
// Include for std::random_device
#include <random>
#include <vector>
#include <sstream>
#include <iomanip>
#include <queue>

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

    // Increment comparisons
    comparisons++; 
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

// Graph
class Vertex {
public:
    int vertexID;
    bool processed;
    vector<Vertex*> neighbors;

    // Constructor
    Vertex(int id) : vertexID(id), processed(false) {}

    // Add a neighbor to the vertex
    void addNeighbor(Vertex* neighbor) {
        neighbors.push_back(neighbor);
    }
};

class Graph {
public:
    vector<Vertex> vertices;

    // Destructor to clear vertices
    ~Graph() {
        vertices.clear();
    }


    // Find a vertex by ID
    Vertex* findVertex(int id) {
        for (auto& vertex : vertices) {
            if (vertex.vertexID == id) {
                return &vertex;
            }
        }
        return nullptr;
    }

    // Add a new vertex to the graph
    void addVertex(int id) {
        vertices.push_back(Vertex(id));
    }

    // Add an edge between two vertices
    void addEdge(int id1, int id2) {
        Vertex* v1 = findVertex(id1);
        Vertex* v2 = findVertex(id2);

        if (v1 && v2) {
            v1->addNeighbor(v2);
            v2->addNeighbor(v1);
        }
    }

    // Print the graph as matrix
    void printMatrix() const {
        // Set the width for column headers
        int columnWidth = 3;

        // Print column headers
        cout << setw(columnWidth) << " ";
        for (const auto& vertex : vertices) {
            cout << setw(columnWidth) << vertex.vertexID;
        }
        cout << endl;

        // Print rows
        for (const auto& vertex : vertices) {
            cout << setw(columnWidth) << vertex.vertexID;
            for (const auto& otherVertex : vertices) {
                bool isNeighbor = false;
                for (const auto& neighbor : vertex.neighbors) {
                    if (neighbor->vertexID == otherVertex.vertexID) {
                        isNeighbor = true;
                        break;
                    }
                }
                cout << setw(columnWidth) << (isNeighbor ? "1" : "0");
            }
            cout << endl;
        }
    }

    // Print the graph as an adjacency list
    void printAdjacencyList() const {
        for (const auto& vertex : vertices) {
            cout << "[" << vertex.vertexID << "] ";
            for (const auto& neighbor : vertex.neighbors) {
                cout << neighbor->vertexID << " ";
            }
            cout << endl;
        }
    }

    // Print the graph as linked objects
    void printLinkedObjects() const {
        for (const auto& vertex : vertices) {
            cout << "Vertex " << vertex.vertexID << ":" << endl;
            cout << "id\t\t " << vertex.vertexID << endl;
            cout << "processed\t " << boolalpha << vertex.processed << endl;
            cout << "neighbors\t [";
            for (size_t i = 0; i < vertex.neighbors.size(); ++i) {
                cout << vertex.neighbors[i]->vertexID;
                if (i < vertex.neighbors.size() - 1) {
                    cout << ",";
                }
            }
            cout << "]" << endl << endl;
        }
    }

    // Depth-first traversal function
    void DFS(Vertex* currentVertex, int& comparisons) {
        if (currentVertex && !currentVertex->processed) {
            cout << currentVertex->vertexID << " ";
            currentVertex->processed = true;

            comparisons++;

            for (Vertex* neighbor : currentVertex->neighbors) {
                if (!neighbor->processed) {
                    DFS(neighbor, comparisons);
                }
            }
        }
    }

    // Wrapper function for DFS to handle different starting points
    void performDFS() {
        for (auto& vertex : vertices) {
            vertex.processed = false;
        }

        int comparisons = 0;

        for (auto& vertex : vertices) {
            if (!vertex.processed) {
                DFS(&vertex, comparisons);
            }
        }

        cout << "\nNumber of comparisons: " << comparisons << endl;
    }

    // Breadth-first traversal function
    void BFS(Vertex* startVertex, int& comparisons) const {
        if (!startVertex) {
            return;
        }

        queue<Vertex*> queue;
        queue.push(startVertex);

        startVertex->processed = true;

        while (!queue.empty()) {
            Vertex* currentVertex = queue.front();
            queue.pop();

            cout << currentVertex->vertexID << " ";

            for (Vertex* neighbor : currentVertex->neighbors) {
                if (!neighbor->processed) {
                    queue.push(neighbor);
                    neighbor->processed = true;

                    comparisons++;
                }
            }
        }
    }

    // Wrapper function for BFS to handle different starting points
    void performBFS() {
        for (auto& vertex : vertices) {
            vertex.processed = false;
        }

        int comparisons = 0;

        for (auto& vertex : vertices) {
            if (!vertex.processed) {
                BFS(&vertex, comparisons);
            }
        }

        cout << "\nNumber of comparisons: " << comparisons << endl;
    }
};


int main() {

    // Read all lines of magicitems.txt and put them in BST
    // Open the magicitems.txt file
    ifstream magicFile("magicitems.txt");

    // Handle failure
    if (!magicFile)
    {
        cerr << "Failed to open magicitems.txt" << endl;
        return 1;
    }

    Node* root = nullptr;

    int index = 0;
    string line;
    while (getline(magicFile, line)) {
        cout << "Inserting " << line << " Path: ";
        root = insert(root, line);
        cout << endl;
        index++;
    }

    magicFile.close();

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
    printf("Average comparisons: %.2f\n\n", averageComparisons);

    // Open the file
    ifstream graphFile("graphs1.txt");

    // Handle failure
    if (!graphFile)
    {
        cerr << "Failed to open graphs1.txt" << endl;
        return 1;
    }

    // Create a pointer to a Graph to hold the current graph
    Graph* currentGraph = nullptr;

    // Process each line in the file
    while (getline(graphFile, line)) {
        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "new" && iss >> command && command == "graph") {
            // "new graph" command
            if (currentGraph) {
                cout << "\nMatrix:\n";
                currentGraph->printMatrix();
                cout << "\nAdjacency List:\n";
                currentGraph->printAdjacencyList();
                cout << "\nLinked Objects:\n";
                currentGraph->printLinkedObjects();
                cout << "\nDepth-First Traversal:\n";
                currentGraph->performDFS();
                cout << "\nBreadth-First Traversal:\n";
                currentGraph->performBFS();
                delete currentGraph;
            }
            currentGraph = new Graph;
            cout << "\nCreated a new graph.\n";
        }
        else if (command == "add") {
            string subcommand;
            iss >> subcommand;

            if (subcommand == "vertex") {
                // "add vertex" command
                int id;
                if (iss >> id) {
                    currentGraph->addVertex(id);
                }
            }
            else if (subcommand == "edge") {
                // "add edge" command
                int id1, id2;
                char hyphen;
                if (iss >> id1 >> hyphen >> id2 && hyphen == '-') {
                    currentGraph->addEdge(id1, id2);
                }
            }
        }
    }

    // Print and delete the final graph
    if (currentGraph) {
        cout << "\Matrix:\n";
        currentGraph->printMatrix();
        cout << "\nAdjacency List:\n";
        currentGraph->printAdjacencyList();
        cout << "\nLinked Objects:\n";
        currentGraph->printLinkedObjects();
        cout << "\nDepth-First Traversal:\n";
        currentGraph->performDFS();
        cout << "\nBreadth-First Traversal:\n";
        currentGraph->performBFS();
        delete currentGraph;
    }

    // Close the file
    graphFile.close();

    return 0;
}