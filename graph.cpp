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
#include "utils.cpp"

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
    void addEdge(int src, int dest, float weight, int transportMethod)
    {   
        auto temp = new Edge(nodes[src], nodes[dest], weight, transportMethod);
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
        int lineCounter = 0;
        while(getline(dataFile, line))
        {
            lineCounter++;
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
                    vector<string> coordinatesTokens;

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
                float weight = stof(tokens[2]);
                if(nodes[nodeMap[destination]].name == "Punto 1 Bus")
                {
                    cout<<origin<<"|"<<destination<<" "<<nodeMap[destination]<<" "<<nodes[nodeMap[origin]].name<<endl;
                }
                addEdge(nodeMap[origin], nodeMap[destination], weight, transportCounter);
            }
            tokens.clear();
            
        }
        transportCounter++;
        dataFile.close();
        cout<<"Data read "<<file<<" "<<lineCounter<<endl;
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