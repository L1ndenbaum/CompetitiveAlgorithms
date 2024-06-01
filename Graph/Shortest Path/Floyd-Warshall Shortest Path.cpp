#include "../../Heads/Head.h"
#define V 4
/*
    Floyd使用dp思想 定义dp[k][i][j]为包括了前1-k个点的子图,从i走到j的最短路径
    转移方程为dp[k][i][j]=min(dp[k-1][i][j],dp[k][i][k]+dp[k][k][j])
    使用滚动数组优化掉一维空间。
    竞赛中可以直接用最短路径数组dp[][]当作邻接矩阵存图,令INF=0x3f3f3f3f3f3f3f3f
    dp[i][i]为从i出发,经过其他点绕一圈回到自己的最短路径,
    dp[i][i]<0,说明存在负圈,可利用这一点判断图中是否有负圈。
*/

/*
Floyd-Warshall算法可以处理带负权值的图 并且在有向带权图和无向带权图中均可以使用
但是不可以处理带负值环的图(一个环内的节点的边的权值和为负数)
*/
class WeightedGraph
{
public:
    int AdjMAT[V][V] = {{0, 5, INT_MAX, 10},
                        {INT_MAX, 0, 3, INT_MAX},
                        {INT_MAX, INT_MAX, 0, 1},
                        {INT_MAX, INT_MAX, INT_MAX, 0}};
    int path[V][V]; // path[i][j]=u 表示从i到j的最短路径,从i出发下一个点是u
    void PrintPath(int u, int v)
    {
        cout << "From " << u << " to " << v << ":" << endl;
        cout << "Disance :" << AdjMAT[u][v] << endl;
        cout << "Path : " << endl
             << u;
        int current = u;
        while (current != v)
        {
            cout << "--->" << path[current][v];
            current = path[current][v];
        }
        cout << endl;
    }
    void PrintSolution()
    {
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (AdjMAT[i][j] != INT_MAX && i != j)
                    PrintPath(i, j);
    }
    void FloydWarshall()
    {
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                path[i][j] = j; // 对path[][]的初始化
        for (int k = 0; k < V; k++)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                {
                    if (AdjMAT[i][j] > (AdjMAT[i][k] + AdjMAT[k][j]) && (AdjMAT[k][j] != INT_MAX && AdjMAT[i][k] != INT_MAX))
                    {
                        AdjMAT[i][j] = AdjMAT[i][k] + AdjMAT[k][j];
                        path[i][j] = path[i][k]; // 标记到该点的前一个点
                    }
                }
            }
        }
        PrintSolution();
    }
};
// 时间复杂度:O(V^3)