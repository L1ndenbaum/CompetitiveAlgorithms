#include "../../Heads/Head.h"
class DirectedGraph
{
    void TopologicalSortUtil(int v, bool *vis, stack<int> &st);
    void AllTopologicalSortUtil(vector<int> &res, bool *vis);
    int V;
    list<int> *AdjList;
    vector<int> Indegree;

public:
    DirectedGraph(int N)
    {
        V = N;
        AdjList = new list<int>[N];
        Indegree.resize(N);
    }
    void AddEdge(int u, int v);
    void TopologicalSort();    // 找到一个可能的拓扑排序的时间复杂度: O(V+E)
    void AllTopologicalSort(); // 找到所有可能的拓扑排序的最坏时间复杂度: O(V!) 比如没有任何一条边的图
};
void DirectedGraph::AddEdge(int u, int v)
{
    AdjList[u].push_back(v);
    Indegree[v]++;
}
void DirectedGraph::TopologicalSortUtil(int v, bool *vis, stack<int> &res)
{
    vis[v] = true; // 标记当前节点已访问
    list<int>::iterator it;
    for (it = AdjList[v].begin(); it != AdjList[v].end(); it++) // 对一个节点的所有临边调用
        if (!vis[*it])
            TopologicalSortUtil(*it, vis, res);
    res.push(v); // 当一个节点的所有临边全部访问后，这个节点入栈
}
void DirectedGraph::TopologicalSort()
{
    stack<int> res;          // 存放节点的栈
    bool *vis = new bool[V]; // 记录节点是否被访问
    memset(vis, 0, sizeof(bool) * V);
    for (int i = 0; i < V; i++)
        if (!vis[i])
            TopologicalSortUtil(i, vis, res);
    while (!res.empty())
    {
        cout << res.top() << ' ';
        res.pop();
    }
    delete[] vis;
}
void DirectedGraph::AllTopologicalSort()
{
    bool *vis = new bool[V];
    memset(vis, 0, sizeof(bool) * V);
    vector<int> res;
    AllTopologicalSortUtil(res, vis);
}
void DirectedGraph::AllTopologicalSortUtil(vector<int> &res, bool *vis)
{
    bool AllFound = false;
    for (int i = 0; i < V; i++)
    {
        if (Indegree[i] == 0 && !vis[i]) // 如果一个点的入度为0并且还没有访问过，那么这个点就是当前优先级最高的点，从这个点开始
        {
            // 这样与这个点相邻的所有点的入度均减少1
            list<int>::iterator j;
            for (j = AdjList[i].begin(); j != AdjList[i].end(); j++)
                Indegree[*j]--;
            res.push_back(i); // 这个入度为0的节点入栈
            vis[i] = true;    // 置为已访问
            AllTopologicalSortUtil(res, vis);
            // 重置vis,res,Indegree以便回溯
            vis[i] = false;           // 回溯过程 将i置为未访问
            res.erase(res.end() - 1); // 从节点栈里剔除刚才入栈的节点
            for (j = AdjList[i].begin(); j != AdjList[i].end(); j++)
                Indegree[*j]++;
            AllFound = true; // 所有节点都被访问过后，不会进入这个if AllFound本就是false,所以之后用if(!AllFound)输出结果
        }
    }
    if (!AllFound) // 如果所有节点都被访问过了，那么就输出一种可能的拓扑排序的结果
    {
        for (int i = 0; i < res.size(); i++)
            cout << res[i] << " ";
        cout << endl;
    }
}