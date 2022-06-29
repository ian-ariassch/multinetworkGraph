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
    float speed;
public:
    float weight;
    int transportMethod;

    Edge()
    {
        weight = INT_MAX;
        transportMethod = -1;
    }

    Edge(Node src, Node dest, float speed, int transportMethod) {
        this->src = src;
        this->dest = dest;
        this->speed = speed;
        this->transportMethod = transportMethod;
        calculateWeight();
        cout<<"Edge created: "<<src.getId()<<" "<<dest.getId()<<" "<<weight<<endl;
    }

    void calculateWeight() {
        float d = calculateHarvesineDistance(src, dest);
        // cout<<d<<endl;
        weight = d/speed;
    }
};