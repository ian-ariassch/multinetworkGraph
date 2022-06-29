#include "graph.cpp"

float calculateNodeDistances(Graph *g, int originId, int destinationId)
{
    auto origin = g->nodes[originId];
    auto destination = g->nodes[destinationId];
    return calculateHarvesineDistance(origin,destination);
    
}

pair<int,float> findClosestValidStation(Graph *g, int startingId, vector<bool> selectedStations)
{
    int closestId = -1;
    int walkingSpeed = 10;
    float closestDistance = INT_MAX;
    for (int destinationNode = 0; destinationNode < g->getNodeCounter(); destinationNode++)
    {
        auto nodeStations = g->nodes[destinationNode].stationType;
        bool isValid = 0;
        for(int i = 0; i < nodeStations.size(); i++)
        {
            if(nodeStations[i] == selectedStations[i] == 1)
            {
                isValid = 1;
                // break;
            }
        }
        if (isValid)
        {
            float distance = calculateNodeDistances(g,startingId,destinationNode); 
            if (distance < closestDistance)
            {
                closestDistance = distance;
                closestId = destinationNode;
            }
        }
    }

    return make_pair(closestId, closestDistance/walkingSpeed);
}



pair<vector<float>,vector<pair<int,string>>> dijkstra(Graph *g, string originName, vector<bool> selectedStations, vector<string> stationsIds, float &addedTime)
{
    int src = g->nodeNameMap[originName];
    int graphSize = g->getNodeCounter();
    vector<float> shortestPath(graphSize, INT_MAX);
    vector<pair<int,string>> previousNode;
    vector<bool> visited(graphSize, 0);

    auto closestValidStation = findClosestValidStation(g, src, selectedStations);
    
    addedTime = closestValidStation.second;

    src = closestValidStation.first;


    for(int i = 0; i < graphSize; i++)
    {
        shortestPath.push_back(INT_MAX);
        
        previousNode.push_back(make_pair(-1,""));

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
        for (auto edge : g->adj[minIndex])
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

void printShortestRoute(pair<vector<float>,vector<pair<int,string>>> dijkstraData, string destinationName, Graph *g, vector<bool> selectedStations, float startingTime)
{
    int destinationId = g->nodeNameMap[destinationName];

    auto closestValidDestinationStation = findClosestValidStation(g, destinationId, selectedStations);

    destinationId = closestValidDestinationStation.first;
    float finishingTime = closestValidDestinationStation.second;
    
    stack<string> route;
    int ParentNodeId = dijkstraData.second[destinationId].first;
    cout<<ParentNodeId<<endl;
    if(ParentNodeId == -1)
    {
        cout<<"No route found"<<endl;
        return;
    }
    auto ParentNode = g->nodes[ParentNodeId];
    auto ParentNodeTransportMethod = dijkstraData.second[destinationId].second;
    
    route.push(destinationName);
    while(dijkstraData.second[ParentNodeId].first != ParentNodeId)
    {
        route.push(ParentNode.name + " take " + ParentNodeTransportMethod + " to:");
        ParentNodeId = dijkstraData.second[ParentNodeId].first;
        ParentNode = g->nodes[ParentNodeId];
        ParentNodeTransportMethod = dijkstraData.second[ParentNodeId].second;
    }
    route.push("Start from: "+ParentNode.name);
    while(!route.empty())
    {
        cout<<route.top()<<endl;
        route.pop();
    }
    cout<<"Travel Time: "<<dijkstraData.first[destinationId]*60 + (startingTime + finishingTime)*60<<endl;
    cout<<"Lost "<<(startingTime + finishingTime) * 60<<" minutes"<<endl;

}