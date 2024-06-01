#include "../Heads/Head.h"
// 图论
// 一、图的基本概念
/*
图这种抽象模型由点(Vertex)和连接点的边(Edge)组成。很多点和边构成了一个网状结构，从而能方便地描述事物之间的间接关系。
图算法的复杂度和点的数量n、边的数量m直接相关。一个能达到O(n+m)复杂度的算法即为解决图问题的最好程度。
由于复杂度和n、m都有关系，因此n、m的情况对算法的选择有影响，稀疏图和稠密图适用于不同的算法。
如果n和m的数量级相同，那就是稀疏图。如果m很大，例如极端情况下每两个点之间都有边连接，m约等于(n^2)/2,则是稠密图
图的基本特征是点和边，图的基本算法是用搜索来处理点和边的关系。
图的一个基本问题是连通性检查，判断图中所有点的点之间是否连通。
*/

// 二、图的存储
/*
常用三种数据结构储存图：邻接矩阵、邻接表、链式前向星。
邻接矩阵和邻接表适用于绝大多数情况，而链式前向星非常省空间，可应用于极大的图中。
除了以上3种方法，还可以直接用数组储存起点u、终点v、边长w的三元组{u,v,w}。
但这种方法的缺陷就是无法快速定位点和边，所以应用场景较少。
*/

/*
1.邻接矩阵
邻接矩阵是最简单、最容易操作的储存方法，特别适用于稠密图，且图越稠密越好。如果用与稀疏图，则非常浪费空间。

定义int graph[N][N]二维数组用来储存图。 graph[i][j]的值是从点i到j的边的权值

将边分成两种情况，无向边和有向边，分别对应无向图和有向图。
(1)无向图：graph[i][j]=graph[j][i]
(2)有向图：graph[i][j]!=graph[j][i]
如果点i和j之间没有边，可以定义一个极大值INF，用graph[i][j]=INF表示i和j之间没有边。

邻接矩阵的优点如下：
[1]适合稠密图
[2]代码简短，对边的存储、查询、更新等操作快且简单，只需要一步就能实现访问和修改边
邻接矩阵的缺点如下：
[1]储存的空间复杂度为O(N^2)，太高了，不适合稀疏图
[2]一般情况下不能储存重边。
(u,v)之间可能有两条或更多条边，这就是重边。
重边的出现是因为点和点之间的边可能需要定义不用的度量，如费用、长度等，不能合并为一个度量。
有向边(u,v)在矩阵中只能储存一个参数，矩阵本身的局限性使它不能储存重边，
不过如果这个参数值只是用来表示边的数量，那么也算储存了重边。
*/

/*
2.邻接表
邻接表只储存存在的边，不储存不存在的边，这是邻接表相对与邻接矩阵的优越性。
C++中可以使用vector来实现邻接表。
邻接表特别适用于稀疏图，其有点为储存效率特别高，只需要与边数成正比的空间，
存储的空间复杂度为O(n+m)；而且能存储重边。
缺点为变成比邻接矩阵稍微麻烦一些，访问和修改的效率也慢一些。
*/

class UndirectedGraph_unweighted // 无向无权图
{
    int VexAmount;
    list<int> *AdjList;

public:
    void InitializeGraph(int n)
    {
        VexAmount = n;
        AdjList = new list<int>[n];
    }
    void AddEdge(int u, int v)
    {
        AdjList[u].push_back(v);
        AdjList[v].push_back(u);
    }
    bool IsCyclicUtility(int v, bool *vis, int parent)
    {
        vis[v] = true;
        for (auto it : AdjList[v])
        {
            if (!vis[it])
            {
                if (IsCyclicUtility(it, vis, v))
                    return true;
            }
            else if (it != parent)
                return true;
        }
        return false;
    }
    bool IsCyclic()
    {
        bool *vis = new bool[VexAmount];
        memset(vis, 0, sizeof(bool) * VexAmount);
        for (int i = 0; i < VexAmount; i++)
            if (!vis[i])
                if (IsCyclicUtility(i, vis, -1))
                    return true;
        return false;
    }
};

