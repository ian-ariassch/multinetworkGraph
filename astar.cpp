#include "dijkstra.cpp"

float heuristic(Graph *g, int originId, int destinationId)
{
    auto origin = g->nodes[originId];
    auto destination = g->nodes[destinationId];
    return sqrt(pow(origin.getCoordX() - destination.getCoordX(), 2) + pow(origin.getCoordX() - destination.getCoordY(), 2));
}


vector<float> Astar(Graph *g, string originName, string destinationName, vector<bool> selectedStations, vector<string> stationsIds, bool print)
{
    int originId = g->nodeNameMap[originName];
    int destinationId = g->nodeNameMap[destinationName];
    set<pair<float,int>> openList;
    vector<float> Gcost, Fcost;
    vector<pair<int,string>> parent;
    map<int,bool> isInOpenList;


    for(int node = 0; node < g->getNodeCounter(); node++)
    {
        Gcost.push_back(INT_MAX);
        Fcost.push_back(INT_MAX);
        // Hcost.push_back(heuristic(g, originId, node));
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
            cout<<"broke in "<<i<<" iterations"<<endl;
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
        // cout<<ParentNodeId<<endl;
        route.push(ParentNode.name + " via " + ParentNodeTransportMethod);
        ParentNodeId = parent[ParentNodeId].first;
        //  cout<<ParentNodeId<<" 2 "<<endl;
        ParentNode = g->nodes[ParentNodeId];
        ParentNodeTransportMethod = parent[ParentNodeId].second;
    }
    route.push(originName);
    while(!route.empty())
    {
        cout << route.top() <<endl;
        route.pop();
    }}

    cout<<"Reached from "<<originName<<" to "<<destinationName<<" in "<<Gcost[destinationId] * 60<<" minutes"<<endl;

    return Gcost;
}