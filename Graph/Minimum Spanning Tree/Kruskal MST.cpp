#include "../../Heads/Head.h"
class UndirectedGraph_weighted_AdjList
{
public:
    class DJU
    {
    public:
        int *s, *rank;
        DJU(int N)
        {
            s = new int[N];
            rank = new int[N];
            for (int i = 0; i < N; i++)
                s[i] = i, rank[i] = 1;
        }
        int FindRoot(int x)
        {
            return s[x] = (s[x] == x ? x : FindRoot(s[x]));
        }
        void Merge(int x, int y)
        {
            x = FindRoot(x), y = FindRoot(y);
            if (x == y)
                return;
            if (rank[x] > rank[y])
                swap(x, y);
            s[x] = y;
            if (rank[x] == rank[y])
                rank[y]++;
        }
    };
    int VertexN;
    vector<vector<int>> EdgeList;
    UndirectedGraph_weighted_AdjList(int N)
    {
        VertexN = N;
    }
    void AddEdge(int u, int v, int w)
    {
        EdgeList.push_back({w, u, v});
    }
    void Kruskal_MST() // Kruskal最小生成树算法
    {
        sort(EdgeList.begin(), EdgeList.end());
        sort(EdgeList.begin(), EdgeList.end(), less<PII>());
        DJU S(VertexN);
        int tot_w = 0;
        for (auto edge : EdgeList)
        {
            int weight = edge[0], v = edge[1], u = edge[2];
            if (S.FindRoot(u) != S.FindRoot(v))
            {
                S.Merge(u, v);
                tot_w += weight;
                cout << u << "--" << v << "=" << weight << endl;
            }
        }
        cout << "Total Cost:" << tot_w << endl;
    }
    // Kruskal最小生成树时间复杂度：O(EdgeN*log(EdgeN))
};
