#include "graph.cpp"

pair<vector<float>,vector<pair<int,string>>> dijkstra(Graph g, string originName, vector<bool> selectedStations, vector<string> stationsIds)
{
    int src = g.nodeNameMap[originName];
    int graphSize = g.getNodeCounter();
    vector<float> shortestPath(graphSize, INT_MAX);
    vector<pair<int,string>> previousNode;
    vector<bool> visited(graphSize, 0);

    for(int i = 0; i < graphSize; i++)
    {
        shortestPath.push_back(INT_MAX);
        
        previousNode.push_back(make_pair(INT_MAX,""));

    }
    shortestPath[src] = 0;
    previousNode[src].first = src;
    previousNode[src].second = originName;
    while (true)
    {
        int min = INT_MAX;
        int minIndex = -1;
        for (int i = 0; i < graphSize; i++)
        {
            if (!visited[i] && shortestPath[i] < min)
            {
                min = shortestPath[i];
                minIndex = i;
            }
        }
        if (minIndex == -1)
        {
            break;
        }
        visited[minIndex] = true;
        for (auto edge : g.adj[minIndex])
        {
            int dest = edge.second.getId();
            float weight = edge.first.weight;
            if (shortestPath[dest] > shortestPath[minIndex] + weight && selectedStations[edge.first.transportMethod])
            {
                shortestPath[dest] = shortestPath[minIndex] + weight;
                previousNode[dest].first = minIndex;
                previousNode[dest].second = stationsIds[edge.first.transportMethod];
            }
        }
    }
    return make_pair(shortestPath,previousNode);
}

void printShortestRoute(pair<vector<float>,vector<pair<int,string>>> dijkstraData, string destinationName, Graph g)
{
    int destinationId = g.nodeNameMap[destinationName];
    
    stack<string> route;
    int ParentNodeId = dijkstraData.second[destinationId].first;
    auto ParentNode = g.nodes[ParentNodeId];
    auto ParentNodeTransportMethod = dijkstraData.second[destinationId].second;
    
    route.push(destinationName);
    while(dijkstraData.second[ParentNodeId].first != ParentNodeId)
    {
        route.push(ParentNode.name + " take " + ParentNodeTransportMethod + " to:");
        ParentNodeId = dijkstraData.second[ParentNodeId].first;
        ParentNode = g.nodes[ParentNodeId];
        ParentNodeTransportMethod = dijkstraData.second[ParentNodeId].second;
    }
    while(!route.empty())
    {
        cout<<route.top()<<endl;
        route.pop();
    }
}