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




float heuristic(Graph *g, int originId, int destinationId)
{
    auto origin = g->nodes[originId];
    auto destination = g->nodes[destinationId];
    return sqrt(pow(origin.getCoordX() - destination.getCoordX(), 2) + pow(origin.getCoordX() - destination.getCoordY(), 2));
}

void Astar(Graph *g, string originName, string destinationName, vector<bool> selectedStations, vector<string> stationsIds, bool print, string file = "")
{
    int originId = g->nodeNameMap[originName];
    int destinationId = g->nodeNameMap[destinationName];
    set<pair<float,int>> openList;
    vector<float> Gcost, Fcost;
    vector<pair<int,string>> parent;
    map<int,bool> isInOpenList;
    cout<<originId<<" "<<destinationId<<endl;
    auto closestValidStation = findClosestValidStation(g, originId, selectedStations);
    
    auto addedTime = closestValidStation.second;


    cout<<closestValidStation.first<<" "<<closestValidStation.second<<endl;

    originId = closestValidStation.first;

    // originName = g->nodes[originId].name;

    closestValidStation = findClosestValidStation(g,destinationId,selectedStations);

    destinationId = closestValidStation.first;

    // destinationName = g->nodes[destinationId].name;

    addedTime += closestValidStation.second;


    for(int node = 0; node < g->getNodeCounter(); node++)
    {
        Gcost.push_back(INT_MAX);
        Fcost.push_back(INT_MAX);
        parent.push_back(make_pair(node,""));
        isInOpenList.insert(make_pair(node,false));
    }
    Gcost[originId] = 0;
    Fcost[originId] = heuristic(g,originId,originId);

    openList.insert(make_pair(Fcost[originId],originId));
    isInOpenList[originId] = true;

    int i = 0;

    while(openList.size() > 0)
    {

        pair<float,int> currentNode = *openList.begin();
        int currentNodeId = currentNode.second;
        openList.erase(openList.begin());
        isInOpenList[currentNodeId] = false;

        if(currentNodeId == destinationId)
        {
            break;
        }
        for(auto edge : g->adj[currentNodeId])
        {
            int neighbor = edge.second.getId();
            float weight = edge.first.weight;
            if(selectedStations[edge.first.transportMethod] && Gcost[currentNodeId] + weight < Gcost[neighbor])
            {
                Gcost[neighbor] = Gcost[currentNodeId] + weight;
                Fcost[neighbor] = Gcost[neighbor] + heuristic(g,originId, neighbor);
                parent[neighbor] = make_pair(currentNodeId, stationsIds[edge.first.transportMethod]);
                if(!isInOpenList[neighbor])
                {
                    openList.insert(make_pair(Fcost[neighbor],neighbor));
                    isInOpenList[neighbor] = true;
                }
            }
        }
        i++;
    }

    if(print){
    stack<string> route;
    int ParentNodeId = parent[destinationId].first;
    auto ParentNode = g->nodes[ParentNodeId];
    auto ParentNodeTransportMethod = parent[destinationId].second;
    route.push(destinationName + " via " + ParentNodeTransportMethod);
    while(parent[ParentNodeId].first != ParentNodeId)
    {
        route.push(ParentNode.name + " via " + ParentNodeTransportMethod);
        ParentNodeId = parent[ParentNodeId].first;
        ParentNode = g->nodes[ParentNodeId];
        ParentNodeTransportMethod = parent[ParentNodeId].second;
    }
    route.push(originName);
    while(!route.empty())
    {
        cout << route.top() <<endl;
        route.pop();
    }}

    // cout<<originId<<" "<<originName<<endl;
    // cout<<destinationId<<" "<<destinationName<<endl;
    cout<<"Reached from "<<originName<<" to "<<destinationName<<" in "<<to_string((Gcost[destinationId] + addedTime )* 60)<<" minutes"<<endl;
    cout<<"Time lost: "<<addedTime*60<<endl;

    writeToFile(file,to_string((Gcost[destinationId] + addedTime)* 60)+"\t");

    Gcost.clear();
    Fcost.clear();
    parent.clear();
    isInOpenList.clear();
    openList.clear();
}