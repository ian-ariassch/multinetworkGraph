#include <iostream>
#include <vector>
#include "node.cpp"
#include <math.h>
#include <climits>

#define M_PI 3.14159265358979323846

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

    float deg2rad(float deg) {
        return deg * (M_PI / 180);
    }

    float calculateDistance(Node src, Node dest)
    {
        float R = 6371;
        float dLat = deg2rad(dest.getCoordX() - src.getCoordX());
        float dLon = deg2rad(dest.getCoordY() - src.getCoordY());
        float a =
            sin(dLat / 2) * sin(dLat / 2) +
            cos(deg2rad(src.getCoordX())) * cos(deg2rad(dest.getCoordX())) *
            sin(dLon / 2) * sin(dLon / 2);
        float c = 2 * atan2(sqrt(a), sqrt(1 - a));
        float d = R * c;
        return d;
    }

    void calculateWeight() {
        float d = calculateDistance(src, dest);
        // cout<<d<<endl;
        weight = d/speed;
    }
};