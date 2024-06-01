#include "../Heads/Head.h"
/*
    树的直径(又称为树的最远点对)是树上最远的两个点的距离
    可由 [1]两次DFS(BFS) [2]树形DP 得到
    [1]能求出最远距离和完整的路径,但是不允许有负权边
    [2]不能求出完整路径,只能求出最远距离,但是可以有负权边
*/

/*
[1]两次DFS求直径
    先从任一点u出发,到达距离u的最远点v,v是直径的一端
    之后从v出发,到达距离v的最远点w,w是直径的另一端
    {v,w}即为树的直径
*/
const int N = 1e5 + 10;
list<PII> Adj[N];                             // PII的first存边的终点,PII的second存权值
int Distance[N];                              // 记录距离
void GetDiameterDFS(int x, int parent, int d) // 计算节点x到每个子节点的距离
{
    Distance[x] = d;
    for (auto it : Adj[x])
        if (it.first != parent)
            GetDiameterDFS(it.first, x, d + it.second);
}
void GetDiameterDFS_main()
{
    int n, u, v, w;
    cin >> n;
    for (int i = 1; i < n; i++) // n个节点的树一共有n-1个边
    {
        cin >> u >> v >> w;
        Adj[u].push_back({v, w});
        Adj[v].push_back({u, w});
    }
    GetDiameterDFS(1, -1, 0); // 计算从任意点(此处为点1)到树上每个节点之间的距离
    int EndPoint1 = 1;
    for (int i = 1; i <= n; i++) // 找与该点最远的节点 为直径的第一个端点
        if (Distance[i] > Distance[EndPoint1])
            EndPoint1 = i;
    GetDiameterDFS(EndPoint1, -1, 0); // 计算从第一个端点到所有点之间的距离
    int EndPoint2 = 1;
    for (int i = 1; i <= n; i++) // 找与第一个端点最远的节点 为直径的第二个端点
        if (Distance[i] > Distance[EndPoint2])
            EndPoint2 = i;
    cout << Distance[EndPoint2]; // 直径长度
}

/*
[2]树形DP求直径
    定义dp[i]为从i出发能到达的最远距离,转移方程为:
    dp[i]=max(dp[i],dp[v]+Len(i,v));  v为所有和i直连的邻居子节点

    定义MaxLen[u]为经过任一点u的最长路径长度,MaxLen[]中的最大值就是树的直径长度
    将u视为树根,其有若干直连的邻居子节点v,则MaxLen[i]的转移方程为:
    MaxLen[i]=max(MaxLen[i],dp[u]+dp[v]+Len(i,v))

    其中的MaxLen并不需要数组实现,因为是一棵树,所以DFS总会走到所有点,逐次更新最大值即可.
*/
int dp[N], MaxLen;
void DFS(int x, int parent)
{
    for (auto it : Adj[x])
    {
        int v = it.first, w = it.second;
        if (v == parent) // v已经算过
            continue;
        DFS(v, x);
        MaxLen = max(MaxLen, dp[x] + dp[v] + w); // 注意此时计算MaxLen时的dp[x]还没有包括子树v
        dp[x] = max(dp[x], dp[v] + w);
    }
}
void GetDiameterDP()
{
    int n, u, v, w;
    cin >> n;
    for (int i = 1; i < n; i++) // n个节点的树一共有n-1个边
    {
        cin >> u >> v >> w;
        Adj[u].push_back({v, w});
        Adj[v].push_back({u, w});
    }
    DFS(1, -1);
    cout << MaxLen;
}
