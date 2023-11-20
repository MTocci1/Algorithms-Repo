#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <iomanip>
#include <queue>

using namespace std;

class Edge {
public:
    int starterID;
    int destinationID;
    int weight;

    // Constructor
    Edge(int start, int dest, int w) : starterID(start), destinationID(dest), weight(w) {}
};

class Vertex {
public:
    int vertexID;
    bool processed;
    vector<Edge> outgoingEdges;

    // Constructor
    Vertex(int id) : vertexID(id), processed(false) {}

    // Add an outgoing edge to the vertex
    void addOutgoingEdge(int start, int dest, int weight) {
        outgoingEdges.emplace_back(start, dest, weight);
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

    // Add a directed edge with weight between two vertices
    void addDirectedEdge(int fromID, int toID, int weight) {
        Vertex* from = findVertex(fromID);
        Vertex* to = findVertex(toID);

        if (from && to) {
            from->addOutgoingEdge(fromID, toID, weight);
        }
    }

    void printAllEdges() const {
        for (const auto& vertex : vertices) {
            for (const auto& edge : vertex.outgoingEdges) {
                cout << vertex.vertexID << " -> " << edge.destinationID << "; Weight = " << edge.weight << endl;
            }
        }
    }
};

int main() {
    // Open the file
    ifstream graphFile("graphs2.txt");

    // Handle failure
    if (!graphFile)
    {
        cerr << "Failed to open graphs1.txt" << endl;
        return 1;
    }

    // Create a pointer to a Graph to hold the current graph
    Graph* currentGraph = nullptr;

    // Process each line in the file
    string line;
    while (getline(graphFile, line)) {
        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "new" && iss >> command && command == "graph") {
            // "new graph" command
            if (currentGraph) {
                // Print all edges
                currentGraph->printAllEdges();
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
                // "add edge" command for directed graph with weight
                int fromID, toID, weight;
                char arrow;
                if (iss >> fromID >> arrow >> toID >> weight && arrow == '-') {
                    currentGraph->addDirectedEdge(fromID, toID, weight);
                }
            }
        }
    }

    // Print and delete the final graph
    if (currentGraph) {
        // Print all edges
        currentGraph->printAllEdges();
        delete currentGraph;
    }

    // Close the file
    graphFile.close();

    return 0;
}