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
        stringstream linestream(line);
        string item;
        while (getline(linestream, item, '|'))
        {
            // std::cout <<  item << endl;
            tokens.push_back(item);
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
    Graph g({20,35});

    g.readData("bus.txt");
    g.readData("railway.txt");

    vector<string> stationsIds = {"bus","railway"};

    vector<bool> selectedStations = {1,1};
    // g.printGraph();
    
    bool print = 0;    
    auto testcases = readTestCases("testcases");
    string fileOutput = "testcaseOutput.txt";
    ofstream dataFile(fileOutput, ios::trunc);
    dataFile.close();
    for(int i = 0; i < testcases.size(); i++)
    {   
        string originName = testcases[i].first;
        string destinationName = testcases[i].second;
        cout<<originName<<" - "<<destinationName;
        cout<<testcases[i].second<<endl;
        // writeToFile("testcaseOutput.txt", "\n" + test.first + "-" + test.second + "\n");
        // // writeToFile(fileOutput, "\n");
        // Astar(&g,originName, destinationName, {1,0}, stationsIds,print,fileOutput);
        // Astar(&g,test.first, test.second, {0,1}, stationsIds,print,fileOutput);
        // Astar(&g,test.first, test.second, {1,1}, stationsIds,print,fileOutput);
        break;
    }

    // cout<<g.nodeNameMap["Punto 40 Tren"]<<endl;

    // Astar(&g,"Punto 26 Bus", "Punto 15 Tren", selectedStations, stationsIds,1,fileOutput);
    // Astar(&g,"Punto 26 Bus", "Punto 1 Bus", selectedStations, stationsIds,1,fileOutput);
    



    // // auto dijkstraData = dijkstra(&g,originName, selectedStations,stationsIds,addedTime);
    // // printShortestRoute(dijkstraData, destinationName, &g, selectedStations, addedTime, print);

    // addedTime = 0;

    // selectedStations = {0,1};
    // auto dijkstraData = dijkstra(&g,originName, selectedStations,stationsIds,addedTime);
    // printShortestRoute(dijkstraData, destinationName, &g, selectedStations, addedTime, print);

    // addedTime = 0;

    // selectedStations = {1,1};
    // dijkstraData = dijkstra(&g,originName, selectedStations,stationsIds,addedTime);
    // printShortestRoute(dijkstraData, destinationName, &g, selectedStations, addedTime, print);
    // endDij = clock();

    // cout<<"Closest Alternative to "<<originName<<" is "<<g.nodes[findClosestAlternativeStation(&g, g.nodeNameMap[originName], selectedStations)].name<<endl;
    
    // findClosestAlternativeStation(&g, g.nodeNameMap[originName], selectedStations);

    // cout<<g.nodes[g.nodeNameMap[originName]].getCoordX()<<endl;
    // cout<<g.nodes[g.nodeNameMap[originName]].getCoordY()<<endl;;

    // cout<<endl;

    // cout<<g.nodes[g.nodeNameMap[destinationName]].getCoordX()<<endl;
    // cout<<g.nodes[g.nodeNameMap[destinationName]].getCoordY()<<endl;

    // cout<<calculateHarvesineDistance(g.nodes[g.nodeNameMap[originName]],g.nodes[g.nodeNameMap[destinationName]])<<endl;


    // double time_taken = double(endDij - startDij) / double(CLOCKS_PER_SEC);
    // cout << "Time taken by Dijkstra is : " << fixed 
    //      << time_taken << setprecision(5);
    // cout << " sec " << endl;

    // time_taken = double(endAstar - startAstar) / double(CLOCKS_PER_SEC);
    // cout << "Time taken by Astar is : " << fixed 
    //      << time_taken << setprecision(5);
    // cout << " sec " << endl;
    return 0;
}