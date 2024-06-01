#include "../Heads/Head.h"
// 欧拉序

/*
    欧拉序是对一棵树的DFS序列,在进入一个节点和退出一个节点时在列表末尾添加这个节点,
    最后组成的列表就是欧拉序
    一个带有N个节点的树的欧拉序需要 2*N-1 个空间储存
*/
const int N = 1e3;
list<int> AdjList[N];
bool vis[N];
vector<int> EulerSequence;
void GetEulerSequence(int x)
{
    vis[x] = true;
    EulerSequence.push_back(x);
    for (auto AdjNode : AdjList[x])
    {
        if (!vis[AdjNode])
        {
            GetEulerSequence(AdjNode);
            EulerSequence.push_back(x);
        }
    }
}