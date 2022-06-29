#include <iostream>
#include <vector>
#include <math.h>
#include <climits>

#define M_PI 3.14159265358979323846

using namespace std;

class Node {
private:
    int id;
    int networksAmount;
    float coordX;
    float coordY;
public:
    string name;
    vector<bool> stationType;

    Node()
    {
        id = 0;
        name = "";
        coordX = 0;
        coordY = 0;
        networksAmount = 0;
        stationType = {};
    };
    
    Node(int id, string name, vector<bool> stationType, float coordX, float coordY) {
        this->id = id;
        this->networksAmount = stationType.size();
        this->name = name;
        this->stationType = stationType;
        this->coordX = coordX;
        this->coordY = coordY;
    }
    int getId() {
        return id;
    }
    float getCoordX() {
        return coordX;
    }
    float getCoordY() {
        return coordY;
    }
};

float deg2rad(float deg) {
    return deg * (M_PI / 180);
}

float calculateHarvesineDistance(Node src, Node dest)
{
    float R = 6371;
    float dLat = deg2rad(dest.getCoordY() - src.getCoordY());
    float dLon = deg2rad(dest.getCoordX() - src.getCoordX());
    float a =
        sin(dLat / 2) * sin(dLat / 2) +
        cos(deg2rad(src.getCoordY())) * cos(deg2rad(dest.getCoordY())) *
        sin(dLon / 2) * sin(dLon / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float d = R * c;
    return d;
}