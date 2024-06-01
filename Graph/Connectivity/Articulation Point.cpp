#include "../../Heads/Head.h"
/*
图的一个割点指的是：
如果这个点消失了，那么一个图会被分为不连通的更多的图
*/

/*
Tarjan算法：
对图的DFS可以生成一个DFS搜索树
如果这个DFS搜索树中的一个点满足以下任意一个条件，那么它就是一个割点：
[1]这个点是DFS搜索树的根，并且至少有两个孩子
[2]这个点不是DFS搜索树的根，但是这个点有一个孩子v，在以v为根的子树中没有节点具有一条到达u节点的父节点的回边

步骤：
做DFS遍历：
[1]在DFS中，维护一个parent数组，parent[i]是节点i的父节点(在递归函数中直接用一个变量而不使用数组)。
[2]检查节点i是否为DFS搜索树的树根(即parent[i]=NULL)，如果是，且i有至少两个孩子，打印i节点。
[3]当i不是根节点时：维护一个数组vis_time[i]储存每一个节点i实际被访问的时间点(i节点被访问的越早，vis_time[i]越小)，
   来检查以节点i的孩子v为根的子树中有无节点具有一条到达u节点的父节点的回边。
[4]对于每个节点i，找到最早访问的那个能从以节点i为根的子树到达的节点
   通过维护一个数组low[],low[i]为i通过无向边可回溯到的最早时间点
   使得low[i]=min(vis_time[i],vis_time[w])，w是一个i的祖先节点并且i的后代节点的某些节点到w有一条回边

只需要将low[v] >= vis_time[u]中的等号去掉 即可求割边数量
*/
class UndirectedGraph
{
    int VertexN;
    list<int> *AdjList;

public:
    UndirectedGraph(int N)
    {
        VertexN = N;
        AdjList = new list<int>[N];
    }
    void DFSTraverse(int v, bool *vis)
    {
        for (auto it : AdjList[v])
        {
            if (!vis[it])
            {
                vis[it] = true;
                DFSTraverse(it, vis);
            }
        }
    }
    bool IsConnected(bool *vis)
    {
        DFSTraverse(0, vis);
        for (int i = 0; i < VertexN; i++)
            if (!vis[i])
                return false;
        return true;
    }
    void AddEdge(int u, int v)
    {
        AdjList[u].push_back(v);
        AdjList[v].push_back(u);
    }
    void GetArticulationPointsUtil(int u, bool *vis, int *vis_time, int *low, int &time, int parent, bool *IsAP) // 一个递归函数 检查u是否为割点
    {
        int children = 0; // u节点在DFS搜索树中的孩子数
        vis[u] = true;    // 这个vis数组不是必要的,通过vis_time[i]=0也可以判断点i是否被访问过
        vis_time[u] = low[u] = ++time;
        for (auto v : AdjList[u]) // 对u节点的所有相邻节点
        {
            if (!vis[v]) // 如果v节点还没被访问，那么它就是u节点的一个孩子
            {
                children++;
                GetArticulationPointsUtil(v, vis, vis_time, low, time, u, IsAP); // 检查以v为根的子树与u的任意一个祖先有没有连接
                low[u] = min(low[u], low[v]);                                    // 如果孩子(v)能回到更早，那么父亲u也能回到更早
                if (parent != -1 && low[v] >= vis_time[u])                       // 第二种情况满足 即通过u的后代v无法回溯到u的祖先，这时u就是割点
                    IsAP[u] = true;
            }
            else if (v != parent) // 否则当节点v不是u的父亲时,更新low[u]的值，即如果能通过v回溯到更早的时间就更新它
            {
                low[u] = min(low[u], vis_time[v]);
            }
        }
        if (parent == -1 && children > 1) // 第一种情况满足
            IsAP[u] = true;
    }
    void GetArticulationPoints()
    {
        bool *vis = new bool[VertexN];
        memset(vis, 0, sizeof(bool) * VertexN);
        if (!IsConnected(vis)) // 先检查图是否连通 Tarjan算法只对连通图使用
        {
            cout << "Not a connected graph!" << endl;
            return;
        }
        int *vis_time = new int[VertexN];
        int *low = new int[VertexN];
        bool *IsAP = new bool[VertexN];
        memset(vis_time, 0, sizeof(int) * VertexN);
        memset(vis, 0, sizeof(bool) * VertexN);
        memset(IsAP, 0, sizeof(bool) * VertexN);
        int time = 0, parent = -1; // time为DFS执行次数，parent[i]=-1表明i为DFS搜索树树根
        GetArticulationPointsUtil(0, vis, vis_time, low, time, parent, IsAP);
        for (int i = 0; i < VertexN; i++)
            if (IsAP[i])
                cout << i << " is a articulation point" << endl;
        delete[] vis, delete[] low, delete[] IsAP;
    }
};