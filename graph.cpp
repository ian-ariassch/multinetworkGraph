#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include "edge.cpp"

using namespace std;

class Graph {
private:
    int V;
    vector<float> speeds;
    vector<Node> nodes;
    vector<vector<pair<Edge,Node>>> adj;
    int nodeCounter = 0;
public:
    Graph(string file, vector<float> speeds) {
        this->speeds = speeds;
    }
    
    void addNode(string name, float lat, float lon)
    {
        auto temp = new Node(nodeCounter, name, {1,1}, lat, lon);
        nodes.push_back(*temp);
        nodeCounter++;
        cout<<"Node "<<name<<" added"<<endl;
        adj.push_back({});
    }
    void addEdge(int src, int dest, int transportMethod)
    {   
        float transportMethodSpeed = speeds[transportMethod];
        adj[src].push_back(make_pair(Edge(nodes[src], nodes[dest], transportMethodSpeed), nodes[dest]));
    };

    void printGraph()
    {
        for(int i = 0; i<nodes.size(); i++)
        {
            cout<<nodes[i].name<<": ";

            for(auto y: adj[i])
            {
                cout<<"{"<<y.first.weight<<",";
                cout<<y.second.name<<"}"<<endl;
            }
        }
    };
};