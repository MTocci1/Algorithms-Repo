#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

class Vertex; 

class Edge {
public:
    Vertex* source;
    Vertex* destination;
    int weight;

    // Constructor
    Edge(Vertex* s, Vertex* d, int w) : source(s), destination(d), weight(w) {}
};

class Vertex {
public:
    int vertexID;
    int distance;
    Vertex* predecessor;
    vector<Edge*> outgoingEdges;

    // Constructor
    Vertex(int id) : vertexID(id), distance(numeric_limits<int>::max()), predecessor(nullptr) {}

    // Add an outgoing edge to the vertex
    void addOutgoingEdge(Vertex* dest, int weight) {
        outgoingEdges.push_back(new Edge(this, dest, weight));
    }
};

class Graph {
public:
    vector<Vertex*> vertices;

    Vertex* findVertex(int id) {
        for (Vertex* vertex : vertices) {
            if (vertex->vertexID == id) {
                return vertex;
            }
        }
        return nullptr;
    }

    Edge* findEdge(int sourceID, int destinationID) {
        Vertex* source = findVertex(sourceID);
        for (Edge* edge : source->outgoingEdges) {
            if (edge->destination->vertexID == destinationID) {
                return edge;
            }
        }
        return nullptr;
    }


    // Add a new vertex to the graph
    void addVertex(int id) {
        vertices.push_back(new Vertex(id));
    }

    // Add a directed edge with weight between two vertices
    void addDirectedEdge(Vertex* from, Vertex* to, int weight) {
        from->addOutgoingEdge(to, weight);
    }

    void printAllEdges() {
        cout << "All Edges and Their Weights:\n";
        for (Vertex* vertex : vertices) {
            for (Edge* edge : vertex->outgoingEdges) {
                cout << edge->source->vertexID << " --> " << edge->destination->vertexID << " weight is " << edge->weight << endl;
            }
        }
        cout << endl;
    }

    // Initialize single source function
    void initializeSingleSource(Vertex* source) {
        for (Vertex* vertex : vertices) {
            vertex->distance = numeric_limits<int>::max();
            vertex->predecessor = nullptr;
        }
        source->distance = 0;
    }

    // Relax function
    void relax(Vertex* u, Vertex* v, int weight) {
        if (v->distance > u->distance + weight) {
            v->distance = u->distance + weight;
            v->predecessor = u;
        }
    }

    // Bellman-Ford algorithm
    bool bellmanFord(Vertex* source) {
        initializeSingleSource(source);

        for (size_t i = 1; i <= vertices.size() - 1; ++i) {
            for (Vertex* vertex : vertices) {
                for (Edge* edge : vertex->outgoingEdges) {
                    relax(edge->source, edge->destination, edge->weight);
                }
            }
        }

        // Print the shortest paths
        cout << "Shortest paths from vertex " << source->vertexID << ":\n";
        for (Vertex* vertex : vertices) {
            if (vertex->distance == numeric_limits<int>::max()) {
                cout << "Vertex " << vertex->vertexID << ": No path" << endl;
            }
            else {
                printPath(source, vertex);
                cout << endl;
            }
        }

        return true;
    }

private:
    // Print the path from source to destination
    void printPath(Vertex* source, Vertex* destination) {
        list<int> path;
        while (destination != nullptr) {
            path.push_front(destination->vertexID);
            destination = destination->predecessor;
        }

        auto it = path.begin();
        int prevVertexID = *it;
        int totalCost = 0;
        ++it;
        for (; it != path.end(); ++it) {
            Vertex* currentVertex = findVertex(*it);
            totalCost += findEdge(prevVertexID, *it)->weight;
            prevVertexID = *it;
        }

        // Print the starting and ending vertices
        cout << source->vertexID << " --> " << *path.rbegin() << " cost is " << totalCost << "; path: ";

        // Print the path
        for (it = path.begin(); it != path.end(); ++it) {
            cout << *it;
            if (next(it) != path.end()) {
                cout << " --> ";
            }
        }
    }
};

int main() {
    Graph graph;

    // Open the file
    ifstream graphFile("graphs2.txt");

    // Handle failure
    if (!graphFile) {
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
                // Print all edges before running Bellman-Ford
                currentGraph->printAllEdges();
                // Run Bellman-Ford algorithm
                currentGraph->bellmanFord(currentGraph->vertices[0]);
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
                    Vertex* fromVertex = currentGraph->findVertex(fromID);
                    Vertex* toVertex = currentGraph->findVertex(toID);
                    currentGraph->addDirectedEdge(fromVertex, toVertex, weight);
                }
            }
        }
    }

    // Print and delete the final graph
    if (currentGraph) {
        // Print all edges before running Bellman-Ford
        currentGraph->printAllEdges();
        // Run Bellman-Ford algorithm
        currentGraph->bellmanFord(currentGraph->vertices[0]);
        delete currentGraph;
    }

    // Close the file
    graphFile.close();

    return 0;
}
