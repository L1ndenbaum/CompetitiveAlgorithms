#include "../Heads/Head.h"
class UndirectedGraph_weighted // 无向带权图
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
    int V;
    vector<vector<int>> EdgeList;
    UndirectedGraph_weighted(int N)
    {
        V = N;
    }
    void AddEdge(int u, int v, int w)
    {
        EdgeList.push_back({w, u, v});
    }
};