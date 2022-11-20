#include <iostream>
#include <vector>
#include "node.cpp"
#include <math.h>
#include <climits>

using namespace std;

class Edge {
private:
    Node src;
    Node dest;
public:
    float weight;
    int transportMethod;

    Edge()
    {
        weight = INT_MAX;
        transportMethod = -1;
    }

    Edge(Node src, Node dest, float weight, int transportMethod) {
        this->src = src;
        this->dest = dest;
        this->transportMethod = transportMethod;
        this->weight = weight;
        cout<<"Edge created: "<<src.getId()<<" "<<dest.getId()<<" "<<weight<<endl;
    }
};