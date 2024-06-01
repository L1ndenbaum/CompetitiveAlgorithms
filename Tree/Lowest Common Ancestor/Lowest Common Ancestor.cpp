#include "../../Heads/Head.h"
// LCA: 最近公共祖先

/*
    公共祖先:在一棵有根树上,如果节点A是节点x的祖先,也是节点y的祖先,称A是节点x和y的公共祖先
    最近公共祖先:在x和y的所有公共祖先中,深度最大的成为最近公共祖先,记为LCA(x,y)

    LCA的性质:
    [1]在所有的公共祖先中,LCA(x,y)到x和y的距离都最短
    [2]x,y间最短的路径经过LCA(x,y)
    [3]x,y本身也可以是他们自己的公共祖先,如果y是x的祖先,有LCA(x,y)=y

    求LCA的方法:
    [1]倍增法 时间复杂度O(NlogN+MlogN) M为查询次数 是在线算法 能单独处理每个查询
    [2]Tarjan算法(DFS+并查集) 时间复杂度O(n+m) 最快. 是离线算法 需要统一处理所有查询
*/

/*
法一:倍增法求LCA:
    对于点x和y,如果x比y深,则先将x走到和y相同高度,如果发现y就是x的祖先,记为LCA(x,y)=y
    否则x和y同时向上走,每走一步判断相遇,相遇点为LCA(x,y)
    一步一步向上走很慢,所以用倍增,以2的倍数向上跳进行加速
    已知条件时每个节点知道它的子节点和父节点,并且DFS已经计算了每个节点在书上的深度

    [1]将x与y提到相同的深度,需要提前计算出一些x的祖先节点,作为x的跳板,以便x快速跳到和y相同的高度
       这些预计算的祖先是每个节点的第2^i个祖先(i从0开始),跳的时候先用大数再用小数
       快速预计算每个节点的倍增的祖先:定义parent[x][i]为x的第2^i个祖先,有
       parent[x][i]=parent[parent[x][i-1]][i-1];
       parent[x][0]即为x的父节点
       计算所有节点的parent[][],时间复杂度为O(NlogN)
    [2]x和y同时向上跳,找到LCA
       从一个节点跳到根节点,最多跳logn次,假设从x、y出发,从最大的i=logn开始,跳2^i步,到祖先parent[x][i]和parent[y][i],有以下两种情况
       (1)parent[x][i]=parent[y][i],这个点是一个公共祖先,但不一定是最近的,有可能跳过头了,就换一个小的i重新跳一次
       (2)parent[x][i]!=parent[y][i],则更新x和y为对应的parent[x][i]和parent[y][i],从新的起点继续开始跳
          由于新的x和y深度比原来位置减少超过一半,再跳时只需要跳2^(i-1)步
          (1)(2)包括了比LCA(x,y)深和浅的两种位置,用i循环判断以上两种情况,即从深浅两侧逐渐逼近LCA,
          每循环一次,i--,当i为0时,x和y正好位于LCA的下一层,父节点parent[x][0]就是LCA
          一次查询的时间复杂度为O(logm)
*/
int n, Q, Root; // 节点个数 询问个数 根节点序号
list<int> Adj[N];
int father[N][20], Depth[N];    // 倍增的数组和节点的深度
void DFSInit(int x, int parent) // 求树节点的深度和初始化倍增表 初始化从树根节点开始
{
    Depth[x] = Depth[parent] + 1;
    father[x][0] = parent;
    for (int i = 1; (1 << i) <= Depth[x]; i++) // 求倍增表,最多到根节点
        father[x][i] = father[father[x][i - 1]][i - 1];
    for (auto AdjNode : Adj[x]) // 遍历x的所有孩子进行初始化
        if (AdjNode != parent)
            DFSInit(AdjNode, x);
}
int GetLCA_Multiplication(int x, int y)
{
    if (Depth[x] < Depth[y]) // 总让x处于最底层
        swap(x, y);
    for (int i = 19; i >= 0; i--)            // 让x和y到相同的高度,这里x最多跳19次
        if (Depth[x] - (1 << i) >= Depth[y]) // 如果x跳过头了,就换一个小的i重新跳 也可以写Depth[father[x][i]] >= Depth[y]
            x = father[x][i];                // 如果x还没跳到y的层,就更新x继续跳
    if (x == y)                              // y就是x的祖先
        return y;
    for (int i = 19; i >= 0; i--)         // x和y处于同一层,同步开始跳,如果祖先相等,说明跳过头了,换一个小的i
        if (father[x][i] != father[y][i]) // 当两者不等时,更新位置继续跳
            x = father[x][i], y = father[y][i];
    return father[x][0];
}
void LCA_main1()
{
    int u, v;
    scanf("%d %d %d", &n, &Q, &Root);
    for (int i = 1; i < n; i++)
    {
        scanf("%d %d", &u, &v);
        AddEdge(u, v);
    }
    DFSInit(Root, -1); // 计算节点深度并预处理father[][]数组
    while (Q--)
    {
        scanf("%d %d", &u, &v);
        printf("%d\n", GetLCA_Multiplication(u, v));
    }
}
/*
法二:Tarjan算法:
    以树根为起点,只做一次DFS,在DFS的途中标记经过的点,使用后序遍历,
    利用并查集,在遍历中标记各节点的父节点,以加速对祖先的寻找
    如果在执行一个查询时,发现其中一个点已经被访问过,那么这两个点有祖先关系,
    直接调用这个点的并查集的根,就是最近公共祖先。
*/
const int N = 5e5 + 5;
int parent[N], ans[N]; // 这里 parent[i]表示i的父节点,它是一个并查集
list<PII> Query[N];    // first存相关的查询点 second存查询序号
bool vis[N];
void AddEdge(int u, int v)
{
    Adj[u].push_back(v);
    Adj[v].push_back(u);
}
void AddQuery(int u, int v, int QueryIdx)
{
    Query[u].push_back({v, QueryIdx});
    Query[v].push_back({u, QueryIdx});
}
int FindRoot(int x)
{
    return parent[x] = (x == parent[x] ? x : FindRoot(parent[x]));
}
void GetLCA_Tarjan(int x)
{
    vis[x] = true;
    for (auto AdjNode : Adj[x])
    {
        if (!vis[AdjNode])
        {
            GetLCA_Tarjan(AdjNode); // 后序遍历
            parent[AdjNode] = x;    // 合并父节点:将子节点AdjNode合并到父节点x上 注意合并一定在下层递归完成之后进行 因为寻找祖先是从下到上的
        }
    }
    for (auto it : Query[x]) // 查询所有与x有查询关系的y
    {
        int QueryNode = it.first, QueryIdx = it.second;
        if (vis[QueryNode]) // 点对中有一个点已经被访问过,存在祖先关系
            ans[QueryIdx] = FindRoot(QueryNode);
    }
}
void LCA_main2()
{
    int u, v;
    scanf("%d %d %d", &n, &Q, &Root);
    for (int i = 1; i < n; i++)
    {
        parent[i] = i; // 并查集初始化
        scanf("%d %d", &u, &v);
        AddEdge(u, v);
    }
    parent[n] = n;
    for (int i = 1; i <= Q; i++)
    {
        scanf("%d %d", &u, &v);
        AddQuery(u, v, i);
    }
    GetLCA_Tarjan(Root);
    for (int i = 1; i <= Q; i++)
        printf("%d\n", ans[i]);
}