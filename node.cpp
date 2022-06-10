#include <iostream>
#include <vector>

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