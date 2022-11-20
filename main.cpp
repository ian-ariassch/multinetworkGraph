#include "astar.cpp"
#include <time.h>
#include <iomanip>


vector<pair<string,string>> readTestCases(string fileName)
{
    vector<pair<string,string>> testCases;
    ifstream file(fileName);
    string line;
    vector<string> tokens;
    while (getline(file, line))
    {
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        stringstream linestream(line);
        string token;
        while (getline(linestream, token, '-'))
        {
            tokens.push_back(token);
        }
        testCases.push_back(make_pair(tokens[0], tokens[1]));
        tokens.clear();
    }
    return testCases;
}

int main()
{   

    float addedTime = 0;
    clock_t startDij,endDij, startAstar, endAstar;

    cout<<"a";
    Graph g({20,35});

    g.readData("bus.txt");
    g.readData("railway.txt");
    cout<<g.nodes[g.nodeNameMap["Punto 22 Bus"]].getCoordX()<<" "<<g.nodes[g.nodeNameMap["Punto 22 Bus"]].getCoordY()<<endl;
    // g.printGraph();

    vector<string> stationsIds = {"bus","railway"};

    vector<bool> selectedStations = {1,1};
    // g.printGraph();
    
    
    bool print = 1;    
    auto testcases = readTestCases("testcases");
    string fileOutput = "testcaseOutput.txt";
    ofstream dataFile(fileOutput, ios::trunc);
    dataFile.close();

    for(int i = 0; i < testcases.size(); i++)
    {   
        string originName = testcases[i].first;
        string destinationName = testcases[i].second;
        cout<<originName<<" - "<<destinationName<<endl;
        // writeToFile("testcaseOutput.txt", "\n" + originName + "-" + destinationName + "\n");
        writeToFile(fileOutput, "\n");
        writeToFile("times.txt", "\n");
        Astar(&g,originName, destinationName, {1,0}, stationsIds,print,fileOutput);
        Astar(&g,originName, destinationName, {0,1}, stationsIds,print,fileOutput);
        Astar(&g,originName, destinationName, {1,1}, stationsIds,print,fileOutput);
    }

    return 0;
}