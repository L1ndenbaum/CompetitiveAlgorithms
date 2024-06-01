#include "../../Heads/Head.h"
// 链式前向星使用静态数组模拟邻接表 不浪费空间 空间效率最高
const int V = 1e6 + 5, E = 2e6 + 5; // 点与边的数量
int Head[V], cnt;                   // Head[u]指向u的一个邻居的存储位置 cnt记录当前存储的是第几条边 cnt可以根据需要赋初值 不一定是0
struct
{
    int Start, // 边的起点 起点不是必要的 可以省去
        End,   // 边的终点
        Next,  // 节点u的下一个邻居
        w;     // 权值
} Edge[V];
void Init() // 初始化
{
    for (int i = 0; i < V; i++) // 点初始化
        Head[i] = -1;
    for (int i = 0; i < E; i++) // 边初始化
        Edge[i].Next = -1;
    cnt = 0;
} // 对于节点默认编号为1-n的图,可以认为初值为0,省去Init()函数
void AddEdge(int u, int v, int w) // 增加一条从u到v,权值为w的边
{
    Edge[cnt].Start = u; // 这句可以不写
    Edge[cnt].End = v;
    Edge[cnt].w = w;
    Edge[cnt].Next = Head[u];
    Head[u] = cnt++;
}