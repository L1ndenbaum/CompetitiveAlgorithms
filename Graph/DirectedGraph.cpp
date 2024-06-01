#include "../Heads/Head.h"
class DirectedGraph // 有向图
{
public:
    int V = 0;
    int DirectedEdgeAmount = 0;
    list<int> *AdjList;
    vector<int> Data;
    void InitGraph(int V, int DirectedEdgeAmount)
    {
        this->V = V;
        this->DirectedEdgeAmount = DirectedEdgeAmount;
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
        bool *vis = new bool[V];
        bool *RecStack = new bool[V];
        memset(vis, false, sizeof(bool) * V);
        memset(RecStack, false, sizeof(bool) * V);
        for (int i = 0; i < V; i++)
            if (!vis[i] && IsCyclicUtility(i, vis, RecStack))
                return true;
        return false;
    }
};