#include "../Heads/Head.h"
class DirectedGraph
{
public:
    int VertexN = 0;
    int EdgeN = 0;
    list<int> *AdjList;
    vector<int> Data;
    DirectedGraph(int V, int EdgeN)
    {
        this->VertexN = V;
        this->EdgeN = EdgeN;
        AdjList = new list<int>[V];
        Data.resize(V);
    }
    void AddEdge(int u, int v)
    {
        AdjList[u].push_back(v);
        Data[v]++;
    }
    bool IsCyclicUtility(int v, bool *vis, bool *RecStack)
    {
        if (!vis[v])
        {
            vis[v] = true;
            RecStack[v] = true;
            for (auto it = AdjList[v].begin(); it != AdjList[v].end(); it++)
            {
                if (!vis[*it] && IsCyclicUtility(*it, vis, RecStack))
                    return true;
                else if (RecStack[*it])
                    return true;
            }
        }
        RecStack[v] = false;
        return false;
    }
    bool IsCyclic()
    {
        bool *vis = new bool[VertexN];
        bool *RecStack = new bool[VertexN];
        memset(vis, false, sizeof(bool) * VertexN);
        memset(RecStack, false, sizeof(bool) * VertexN);
        for (int i = 0; i < VertexN; i++)
            if (!vis[i] && IsCyclicUtility(i, vis, RecStack))
                return true;
        return false;
    }
};