#include "astar.cpp"
#include <time.h>
#include <iomanip>


int main()
{   
    clock_t startDij,endDij, startAstar, endAstar;

    cout<<"a";
    Graph g({4,10});

    g.readData("bus.txt");
    g.readData("railway.txt");

    vector<string> stationsIds = {"bus","railway"};

    vector<bool> selectedStations = {1,1};
    // g.printGraph();
    
    
    string originName = "Punto 72 Bus";
    string destinationName = "Punto 72 Bus";
    startAstar = clock();
        Astar(g,"Punto 72 Bus", "Punto 38 Tren", selectedStations, stationsIds,0);
        // Astar(g,"Punto 18 Tren", "Punto 69 Bus", selectedStations, stationsIds,1);
        // Astar(g,"Punto 33 Bus", "Punto 7 Bus", selectedStations, stationsIds,1);
    endAstar = clock();
    //
    startDij = clock();
     auto dijkstraData = dijkstra(g,"Punto 72 Bus", selectedStations,stationsIds);
     printShortestRoute(dijkstraData, "Punto 38 Tren", g);
    //  dijkstraData = dijkstra(g,"Punto 18 Tren", selectedStations,stationsIds);
    //  printShortestRoute(dijkstraData, "Punto 69 Bus", g);
    //  dijkstraData = dijkstra(g,"Punto 33 Bus", selectedStations,stationsIds);
    //  printShortestRoute(dijkstraData, "Punto 7 Bus", g);
    endDij = clock();



    double time_taken = double(endDij - startDij) / double(CLOCKS_PER_SEC);
    cout << "Time taken by Dijkstra is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;

    time_taken = double(endAstar - startAstar) / double(CLOCKS_PER_SEC);
    cout << "Time taken by Astar is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;
}