#include "graph.cpp"

int main()
{
    cout<<"a";
    Graph g({30,2});
    
    g.readData("bus.txt");
    g.readData("railway.txt");

    g.printGraph();
    return 0;
}