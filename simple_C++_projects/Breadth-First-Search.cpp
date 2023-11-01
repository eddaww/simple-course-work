#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <climits>
#include <unordered_map>

using namespace std;

class Graph {
public:
    using Vertex = int;
    using Node = struct Node {
        Vertex vertex;
        Node* next;
        Node(Vertex v) : vertex(v), next(nullptr) {}
    };

    Graph(int numVertices);
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    ~Graph();
    void addVertex();
    void addEdge(Vertex u, Vertex v);
    void BFS(Vertex source);
    void printPath(Vertex source, Vertex target) const;

private:
    int numVertices;
    unordered_map<Vertex, Node*> adjacencyList;
    unordered_map<Vertex, string> color;
    unordered_map<Vertex, int> distance;
    unordered_map<Vertex, Vertex> parent;
};

Graph::Graph(int numVertices) {
    this->numVertices = numVertices;
}

Graph::Graph(const Graph& other) {
    numVertices = other.numVertices;
    color = other.color;
    distance = other.distance;
    parent = other.parent;

    for (const auto& entry : other.adjacencyList) {
        Node* current = entry.second;
        Node* newList = nullptr;
        Node* newListTail = nullptr;
        while (current != nullptr) {
            Node* newNode = new Node(current->vertex);
            if (newList == nullptr) {
                newList = newNode;
                newListTail = newNode;
            } else {
                newListTail->next = newNode;
                newListTail = newNode;
            }
            current = current->next;
        }
        adjacencyList[entry.first] = newList;
    }
}

Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        numVertices = other.numVertices;
        color = other.color;
        distance = other.distance;
        parent = other.parent;

        for (const auto& entry : adjacencyList) {
            Node* current = entry.second;
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }

        adjacencyList.clear();

        for (const auto& entry : other.adjacencyList) {
            Node* current = entry.second;
            Node* newList = nullptr;
            Node* newListTail = nullptr;
            while (current != nullptr) {
                Node* newNode = new Node(current->vertex);
                if (newList == nullptr) {
                    newList = newNode;
                    newListTail = newNode;
                } else {
                    newListTail->next = newNode;
                    newListTail = newNode;
                }
                current = current->next;
            }
            adjacencyList[entry.first] = newList;
        }
    }
    return *this;
}

Graph::~Graph() {
    for (const auto& entry : adjacencyList) {
        Node* current = entry.second;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

void Graph::addVertex() {
    numVertices++;
}

void Graph::addEdge(Vertex u, Vertex v) {
    Node* newNode1 = new Node(v);
    newNode1->next = adjacencyList[u];
    adjacencyList[u] = newNode1;

    Node* newNode2 = new Node(u);
    newNode2->next = adjacencyList[v];
    adjacencyList[v] = newNode2;
}

void Graph::BFS(Vertex source) {
    for (int i = 0; i < numVertices; i++) {
        color[i] = "WHITE";
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    color[source] = "GRAY";
    distance[source] = 0;

    queue<Vertex> queue;
    queue.push(source);

    cout<<"print tree"<<endl;
    while (!queue.empty()) {
        Vertex u = queue.front();
        queue.pop();

        Node* current = adjacencyList[u];
        while (current != nullptr) {
            Vertex v = current->vertex;
            if (color[v] == "WHITE") {
                color[v] = "GRAY";
                distance[v] = distance[u] + 1;
                parent[v] = u;
                queue.push(v);
                cout << u <<" ->"<< v << endl;
            }
            current = current->next;
          
        }
        
        color[u] = "BLACK";
    }
    cout<<distance.size()<<endl;
}

void Graph::printPath(Vertex source, Vertex target) const {
    if (target == source) {
        cout << source << '\n';
    } else if (parent.at(target) == -1) {
        cout << "No path from " << source << " to " << target << " exists.\n";
    } else {
        printPath(source, parent.at(target));
        cout << target << '\n';
    }
}


int main() {

    int numVertices = 6;
    Graph graph(numVertices);
    
    
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    int source = 3;
    int target = 5;

    graph.BFS(source);

    cout << "Path from " << source << " to " << target << ":\n";
    //graph.printPath(source, target);

    // Adding a new vertex
    graph.addVertex();
    graph.addEdge(6, 0);
    graph.addEdge(6, 2);
    graph.addEdge(6, 5);

    int newTarget = 6;

    graph.BFS(source);

    cout << "Path from " << source << " to " << newTarget << ":\n";
    //graph.printPath(source, newTarget);

    return 0;
}
