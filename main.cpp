#include "graph.cpp"

int main()
{
    Graph g("graph.txt",{30,2});
    g.addNode("A", -12.214925, -77.009733);
    g.addNode("B",-12.208328810124613, -77.0046056069268);
    g.addEdge(0,1,0);
    g.printGraph();
    return 0;
}