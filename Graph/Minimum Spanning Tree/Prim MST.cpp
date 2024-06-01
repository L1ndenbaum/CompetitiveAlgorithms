#include "../../Heads/Head.h"
#define V_N 5
class UndirectedGraph_weighted_AdjMAT
{
public:
    int VertexN;
    // int **AdjMAT;
    UndirectedGraph_weighted_AdjMAT(int N)
    {
        VertexN = N;
        // AdjMAT = new int *[VertexN];
        // for (int i = 0; i < VertexN; i++)
        //     AdjMAT[i] = new int[VertexN];
    }
    int AdjMAT[V_N][V_N] = {{0, 2, 0, 6, 0},
                            {2, 0, 3, 8, 5},
                            {0, 3, 0, 0, 7},
                            {6, 8, 0, 0, 9},
                            {0, 5, 7, 9, 0}};
    int MinKey(int *key, bool *MSTset)//
    {
        int min = INT_MAX, min_index;
        for (int v = 0; v < VertexN; v++)
            if (!MSTset[v] && key[v] < min)
                min = key[v], min_index = v;
        return min_index;
    }
    void PrintMST(int *parent)
    {
        cout << "Edge \tWeight\n";
        for (int i = 1; i < VertexN; i++)
            cout << parent[i] << " - " << i << " \t"
                 << AdjMAT[i][parent[i]] << " \n";
    }
    void Prim_MST() // Prim最小生成树
    {
        int *parent = new int[VertexN];   // parent[i]记录了最小生成树中i节点的上一级是哪个节点
        int *key = new int[VertexN];      // key均初始化为无穷，将第一个被选择的点的key置为0
        bool *MSTset = new bool[VertexN]; // MSTset[i]=true表示节点i已经在最小生成树中
        for (int i = 0; i < VertexN; i++) // 初始化
            key[i] = INT_MAX, MSTset[i] = false;
        key[0] = 0, parent[0] = -1;
        for (int count = 0; count < VertexN - 1; count++)
        {
            int u = MinKey(key, MSTset);                                 // 找到具有最小Key的u节点
            MSTset[u] = true;                                            // 将u节点置为已处理
            for (int v = 0; v < VertexN; v++)                            // 用迭代所有相邻边的方式更新u节点的所有相邻节点的key值
                if (AdjMAT[u][v] && !MSTset[v] && AdjMAT[u][v] < key[v]) // 如果u-v距离小于先前的key[v]，就更新key[v]
                    parent[v] = u, key[v] = AdjMAT[u][v];
        }
        PrintMST(parent);
    }
};