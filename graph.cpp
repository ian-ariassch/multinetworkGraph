#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <fstream>
#include "edge.cpp"
#include <sstream>
#include <map>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

class Graph {
private:
    map<string,int> nodeMap;

    int V;
    vector<float> speeds;
    int nodeCounter = 0;
    int transportCounter = 0;
public:
    map<string,int> nodeNameMap;
    vector<Node> nodes;
    vector<vector<pair<Edge,Node>>> adj;
    Graph(vector<float> speeds) {
        this->speeds = speeds;
    }

    int getNodeCounter() {
        return nodeCounter;
    }
    
    void addNode(string name, float lat, float lon)
    {
        vector<bool> stationType = {0,0};
        stationType[transportCounter] = 1;
        auto temp = new Node(nodeCounter, name, stationType, lat, lon);
        nodes.push_back(*temp);
        cout<<"Node "<<name<<" added"<<endl;
        adj.push_back({});
        nodeCounter++;
    }
    void addEdge(int src, int dest, int transportMethod)
    {   
        float transportMethodSpeed = speeds[transportMethod];
        auto temp = new Edge(nodes[src], nodes[dest], transportMethodSpeed, transportMethod);
        adj[src].push_back(make_pair(*temp, nodes[dest]));
    };

    void readData(string file)
    {
        int nodeAmount = 0;
        int internalNodeCounter = 0;
        ifstream dataFile;
        dataFile.open(file);
        string line;
        vector<string> tokens;
        while(getline(dataFile, line))
        {
            stringstream ss(line);
            string temp;
            while(getline(ss, temp, '|'))
            {
                tokens.push_back(temp);
            }

            if(nodeAmount == 0)
            {
                nodeAmount = stoi(temp);
                tokens.clear();
                continue;
            }
            if(internalNodeCounter < nodeAmount)
            {
                    string nodeName = tokens[0];
                    string coordinates = tokens[1];
                    if(nodeMap.find(coordinates) == nodeMap.end())
                    {
                        float lat = stof(coordinates.substr(0, coordinates.find(" ")));
                        float lon = stof(coordinates.substr(coordinates.find(" ")+1));
                        nodeMap.insert(make_pair(coordinates, nodeCounter));
                        nodeNameMap.insert(make_pair(nodeName, nodeCounter));
                        addNode(nodeName, lat, lon);
                    }
                    else
                    {
                        nodeNameMap.insert(make_pair(nodeName, nodeMap[coordinates]));
                        nodes[nodeMap[coordinates]].stationType[transportCounter] = 1;
                    }

                    internalNodeCounter++;
            }
            else
            {
                string origin = tokens[0];
                string destination = tokens[1];
                addEdge(nodeMap[origin], nodeMap[destination], transportCounter);
            }
            tokens.clear();
            
        }
        transportCounter++;
        dataFile.close();
    }

    void printGraph()
    {
        for(int i = 0; i<nodes.size(); i++)
        {
            cout<<nodes[i].name<<" conectado a:"<<endl;;
    

            for(auto y: adj[i])
            {
                cout<<"{"<<y.first.weight<<",";
                cout<<y.second.name<<"}|";
            }
            cout<<endl;
        }

    };
};