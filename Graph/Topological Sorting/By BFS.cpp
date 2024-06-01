#include "../../Heads/Head.h"
/*
1.从入度为0的点开始,所有入度为0的点入队。如果没有入度为0的点,说明不是有向无环图,不存在拓扑排序。
2.弹出队首a,a的所有邻居入度减1，入度减为0的邻居入队。
3.重复2,直到队列为空。
队列弹出的顺序就是一个拓扑排序。
*/
const int N = 1e5;
list<int> AdjList[N];
int Indegree[N];
int n;
void AddEdge(int u, int v)
{
    AdjList[u].push_back(v);
    Indegree[v]++;
}
void TopologicalSort_BFS()
{
    vector<int> res;
    queue<int> Q;
    for (int i = 1; i <= n; i++)
        if (Indegree[i] == 0)
            Q.push(i);
    if (Q.empty())
    {
        cout << "Not a DAG" << endl;
        return;
    }
    while (!Q.empty())
    {
        int head = Q.front();
        res.push_back(head);
        Q.pop();
        for (auto p : AdjList[head])
        {
            Indegree[p]--;
            if (!Indegree[p])
                Q.push(p);
        }
    }
    for (auto p : res)
        cout << p << ' ';
}
// int main()
// {
//     AddEdge(1, 2);
//     AddEdge(1, 4);
//     AddEdge(3, 4);
//     AddEdge(2, 4);
//     n = 4;
//     TopologicalSort_BFS();
//     //output:1 3 2 4
// }