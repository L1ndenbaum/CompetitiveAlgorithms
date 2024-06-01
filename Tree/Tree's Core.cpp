#include "../Heads/Head.h"
/*
    树的重心:
    树的重心是无根树(不含回路的无向图)的一个概念,是一个节点u
    以树上任意节点为根计算它的子树的节点数,如果节点u的最大子数的节点数最少,u是树的重心
    即: 删除节点u后得到若干棵互不连通的子树,其中最大子树的节点数最少。

    只需做一次DFS,假设以u为根的子树节点总数是SubtreeNodeN[u],
    则SubtreeNodeN[u]=Sum(SubtreeNodeN[i])+1
    以其父节点为根的子树的节点总数为D=n-SubtreeNodeN[u]
    记录这些SubtreeNodeN[i]和D之中的最大值,就得到了u的最大连通块

    注: 删除树的重心后得到的所有互不连通的子树,它们的节点数都 <= n/2个
*/
const int N = 5e4 + 5;
list<int> Adj[N];
int SubtreeNodeN[N], // SubtreeNodeN[u]是以u为根的子树的节点数量
    num = 0, MaxN = 1e9,
    n;           // 总结点数
vector<int> ans; // 存储可能为树的重心的节点 重心可能有多个
void AddEdge(int u, int v)
{
    Adj[u].push_back(v);
    Adj[v].push_back(u);
}
void GetSubtreeNodeNumber(int u, int parent)
{
    SubtreeNodeN[u] = 1;
    int temp = 0;
    for (auto AdjNode : Adj[u]) // 遍历u的所有邻居
    {
        if (AdjNode == parent) // 不递归父节点
            continue;
        GetSubtreeNodeNumber(AdjNode, u);         // 递归地计算以AdjNode为根的子树的节点数量
        SubtreeNodeN[u] += SubtreeNodeN[AdjNode]; // 计算以u为根的节点数量
        temp = max(temp, SubtreeNodeN[AdjNode]);  // 记录u的最大子树的节点数量
    }
    temp = max(temp, n - SubtreeNodeN[u]); // temp即为u的最大连通块的节点数
    if (temp < MaxN)                       // 重心要求最大连通块的节点数最少
    {
        MaxN = temp;
        ans.clear();
        ans.push_back(u);
    }
    else if (temp == MaxN) // 有另外的节点的可能是重心
    {
        ans.push_back(u);
    }
}