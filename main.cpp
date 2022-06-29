#include "astar.cpp"
#include <time.h>
#include <iomanip>

int main()
{   

    float addedTime = 0;
    clock_t startDij,endDij, startAstar, endAstar;

    cout<<"a";
    Graph g({20,35});

    g.readData("bus.txt");
    g.readData("railway.txt");

    vector<string> stationsIds = {"bus","railway"};

    vector<bool> selectedStations = {0,1};
    // g.printGraph();
    
    
    string originName = "Punto 40 Tren";
    string destinationName = "Punto 23 Bus";
    startAstar = clock();
        // auto shortestPath = Astar(&g,originName, destinationName, selectedStations, stationsIds,1);
    endAstar = clock();
    
    startDij = clock();
     auto dijkstraData = dijkstra(&g,originName, selectedStations,stationsIds,addedTime);
     printShortestRoute(dijkstraData, destinationName, &g, selectedStations, addedTime);
    endDij = clock();

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