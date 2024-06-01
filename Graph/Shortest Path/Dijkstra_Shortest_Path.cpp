#include "../../Heads/Head.h"
// Dijkstra算法不能处理带负权值的图
#define V_N 9
class Graph_AdjMAT
{
    int VertexN;
    // int **AdjMAT;

public:
    Graph_AdjMAT(int N)
    {
        VertexN = N;
        // AdjMAT = new int *[N];
        // for (int i = 0; i < N; i++)
        //     AdjMAT[i] = new int[N];
    }
    int AdjMAT[V_N][V_N] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                            {4, 0, 8, 0, 0, 0, 0, 11, 0},
                            {0, 8, 0, 7, 0, 4, 0, 0, 2},
                            {0, 0, 7, 0, 9, 14, 0, 0, 0},
                            {0, 0, 0, 9, 0, 10, 0, 0, 0},
                            {0, 0, 4, 14, 10, 0, 2, 0, 0},
                            {0, 0, 0, 0, 0, 2, 0, 1, 6},
                            {8, 11, 0, 0, 0, 0, 1, 0, 7},
                            {0, 0, 2, 0, 0, 0, 6, 7, 0}};
    /*
    AdjMAT:
    {{0, 4, 0, 0, 0, 0, 0, 8, 0},
      {4, 0, 8, 0, 0, 0, 0, 11, 0},
      {0, 8, 0, 7, 0, 4, 0, 0, 2},
      {0, 0, 7, 0, 9, 14, 0, 0, 0},
      {0, 0, 0, 9, 0, 10, 0, 0, 0},
      {0, 0, 4, 14, 10, 0, 2, 0, 0},
      {0, 0, 0, 0, 0, 2, 0, 1, 6},
      {8, 11, 0, 0, 0, 0, 1, 0, 7},
      {0, 0, 2, 0, 0, 0, 6, 7, 0}};
    */
    // Dijkstra最短路径 用邻接矩阵存图
    int minDistance(int *dist, bool *sptSet)
    {
        // 每次开始轮流迭代找到目前未被处理的节点中到源点距离最小的节点
        int min = INT_MAX, min_index;
        for (int v = 0; v < VertexN; v++)
            if (!sptSet[v] && dist[v] <= min)
                min = dist[v], min_index = v;
        return min_index;
    }
    void printSolution(int *dist)
    {
        cout << "Vertex \t Distance from Source" << endl;
        for (int i = 0; i < VertexN; i++)
            cout << i << " \t\t" << dist[i] << endl;
    }
    void Dijkstra(int src) // 邻接矩阵版
    {
        // dist[]:描述源点dist[src]到每个点dist[i]的最短路径大小 dist[i]初始均为无穷
        // sptSet[]:已经找到最短路径的点的集合
        int dist[VertexN];
        bool sptSet[VertexN];
        for (int i = 0; i < VertexN; i++) // 初始化
            dist[i] = INT_MAX, sptSet[i] = false;
        dist[src] = 0; // 将源点到自己的距离置为0
        for (int count = 0; count < VertexN - 1; count++)
        {
            int u = minDistance(dist, sptSet); // 找到目前到源点距离最小的那个点u
            sptSet[u] = true;                  // 将这个点u置为已处理
            for (int v = 0; v < VertexN; v++)  // 对这个u节点的所有没有找到最短路径的相邻节点
                if (!sptSet[v] && AdjMAT[u][v] && dist[u] != INT_MAX && dist[u] + AdjMAT[u][v] < dist[v])
                    // 如果从源点到u的距离加上u-v边的距离 < 从源点到v的距离,那么就更新从源点到v的距离
                    dist[v] = dist[u] + AdjMAT[u][v];
        }
        printSolution(dist);
    }
    // 时间复杂度: O(V^2)
};

class Graph_EdgeList // 用邻接表存图
{
    int VertexN;
    list<PII> *AdjList; // list< pair <AdjNode,Weight> >
public:
    Graph_EdgeList(int N)
    {
        VertexN = N;
        AdjList = new list<PII>[N];
    }
    class Compare
    {
    public:
        bool operator()(PII a, PII b)
        {
            return a.second > b.second; // 将距离最近的排在前面(小顶堆)
        }
    };
    void AddEdge(int u, int v, int weight)
    {
        AdjList[u].pb(make_pair(v, weight));
        AdjList[v].pb(make_pair(u, weight));
    }
    void Dijkstra(int src)
    {
        priority_queue<PII, vector<PII>, Compare> Q; // pair<weight,index>
        vector<int> dist(VertexN, INT_MAX);
        Q.push(make_pair(0, src));
        dist[src] = 0;
        while (!Q.empty())
        {
            int u = Q.top().second;
            Q.pop();
            for (auto it = AdjList[u].begin(); it != AdjList[u].end(); it++)
            {
                int v = (*it).first, weight = (*it).second;
                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    Q.push(make_pair(dist[v], v));
                }
            }
        }
        // Print shortest distances stored in dist[]
        cout << "Vertex Distance from Source" << endl;
        for (int i = 0; i < VertexN; ++i)
            printf("%d \t\t %d\n", i, dist[i]);
    }
};
// 时间复杂度:O(E*log(V))