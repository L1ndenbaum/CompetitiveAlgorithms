// 并查集
/*
并查集直译为“不相交集合”，其包含三项内容：并 查 集。 并查集是不相交集合上的合并、查询
并查集的经典应用有：检查连通性、最小生成树、Kruskal算法、LCA算法
*/

// 一、并查集的基本操作
/*
并查集：将编号分别为1~n的n个对象划分为不相交集合，在每个集合中选择其中某个元素代表该集合。
并查集适合处理不同集合的关系，它有三个基本操作：初始化、合并、查找。
以“社团”为例：一个城市有n个人，他们被分成不同的社团，
            给出一些人的关系，例如1号和2号是朋友，1号和3号也是朋友，那么他们都属于同一个社团
            在分析完所有的关系后，问有多少个社团、每个人属于哪个社团，给出的n可能是1e6级别的。
1.初始化：
定义一维数组int s[],s[i]是结点i的并查集，因为开始的时候还没有处理点与点之间的朋友关系，
那么每个点属于独立的集，直接初始化s[i]=i,如结点1的集s[1]=1。

2.合并：合并总在根上
加入第一个朋友关系(1,2)。在并查集s中，把结点1合并到结点2，
即：将结点1的集1改为结点2的集2，set[1]=set[2]=2。此时5个人关系用4个集表示，set[2]包括了两个结点
继续加入第二个朋友关系(1,3)
先查找结点1的集，s[1]=2，再查找结点2的集s[2]=2，此时结点2的集是自己，查找结束。
再查找结点3的集s[3]=3，由于s[2]不等于s[3]，因此把结点2的集2合并到结点3的集3，即修改s[2]=3;
现在结点1，2，3都属于同一个集了：s[1]=2,set[2]=3,set[3]=3。另外有两个独立的集s[4]=4,s[5]=5。
继续加入第三个朋友关系(2,4)
先查找结点2的集，s[2]=3，再查找结点3的集s[3]=3，结点3的集是自己，查找结束。
之后查找结点4的集，s[4]=4，由于s[3]不等于s[4]，那么将结点3的集3合并到结点4的集4，即修改s[3]=4;
现在结点1，2，3，4都属于同一个集了：s[1]=2,s[2]=3,s[3]=4,s[4]=4。另外只有一个独立的集s[5]=5。
3.查找：
查找某个结点属于哪个集，这是一个递归过程。
例如查找结点1的集，递归过程为：
s[1]=2,s[2]=3,s[3]=4,s[4]=4,最后结点的值和它的集相等，就找到了根节点的集
4.统计：
统计共有几个集的方法是：有多少结点的集等于自身，就有几个集。
例如s[i]=i，这是一个根节点，是它所在的集的代表。统计根节点的数量，就是集的数量。
在查询连通时，同根即连通
例子中，s[4]=4,s[5]=5，所以有两个集。

注意：并查集是“树的森林”，一个集是一棵树，有多少棵树就有多少个集。
      有些树可能非常细长，变成了一个链表，统计时间复杂度为O(n)。
      这是树的退化现象，使得递归的过程十分耗时。后面的“路径压缩”可以解决这一问题。
*/

/*
并查集的C++代码
(1)初始化用InitSet()。
(2)查找用Find_Root_Path_Compression()，它是一个递归函数 如果x=s[x]，表示这是一个集的根节点，查找结束，否则继续递归查找根。
(3)合并用MergeSet()。合并x和y的集，先递归找到x的集(根)，在递归找到y的集，
   然后把x合并到y的集上。x递归到根节点b,y递归到根节点d,最后合并为set[b]=d;
*/
#include <iostream>
using namespace std;
class DJS_Path_Compression
{
public:
    const int N = 8e5 + 5;
    int *s, *rank;
    void InitSet()
    {
        s = new int[N];
        rank = new int[N];
        for (int i = 0; i <= N; i++)
            s[i] = i;
    }
    int Find_Root_Path_Compression(int x)
    {
        return s[x] = (x == s[x] ? x : Find_Root_Path_Compression(s[x]));
        // 这里使用了路径压缩 不使用路径压缩的代码为return x==s[x]?x:Find_Root_Path_Compression(s[x]);
    }
    void MergeSet(int x, int y)
    {
        int root_x = Find_Root_Path_Compression(x), root_y = Find_Root_Path_Compression(y);
        if (root_x != root_y) // 两个结点的根不同 就合并给同一个根
            s[root_x] = s[root_y];
    }
    /*
    优化方法1:路径压缩
    Find_Root_Path_Compression()递归查询元素i所属的集，需要搜索路径找到根节点，返回的结果是根节点。
    这条查询路径可能很长，从而导致效率很低。
    优化路径的方式为：在返回根节点的时候，顺便把i所属的集改成根节点，那么下次再查询的时候就可以用O(1)的时间得到结果。
    Find_Root_Path_Compression()是一个递归函数，在返回的时候，整个递归路径上的结点，它们的集都改为了根节点。
    路径压缩对合并也有用，因为合并需要先查询，而查询会用到路径压缩。
    路径压缩之前，查询和合并的时间复杂度都是O(n)。经过压缩之后，时间复杂度都为O(1)
    */
};

class DJS_Union_By_Rank
{
public:
    const int N = 8e5 + 5;
    int *s, *Rank; // s为并查集集合本身 Rank为节点的秩
    void InitSet()
    {
        s = new int[N];
        Rank = new int[N];
        for (int i = 0; i <= N; i++)
            s[i] = i;
    }
    int FindRoot(int x)
    {
        return x == s[x] ? x : FindRoot(s[x]);
        /*
        while(s[x]^x)
            x=s[x];
        return x;
        也可以使用非递归的循环写法 递归写法在规模太大时可能会爆栈
        */
    }
    void MergeSet(int x, int y)
    {
        x = FindRoot(x), y = FindRoot(y);
        if (x == y)
            return;
        if (Rank[x] > Rank[y]) // 保证Rank[x]<Rank[y] 即总向树的高度较高的那棵树上接
            swap(x, y);
        s[x] = y;               // 不论大于 还是等于 都完成嫁接操作 (若等于，之后要做额外修改) 将秩小的指向秩大的
        if (Rank[x] == Rank[y]) // 如果合并前两棵树一样高，那么合并后
            Rank[y]++;
    }
    /*
    优化方法2:按秩合并
    创建秩数组rank[] 其规模与并查集s[]规模一致 即rank[N]
    如果s[i]是一个集的根节点 那么rank[i]代表了这个根的每一棵子树的最大高度。
    当合并时，总是高的树向矮的树的根上面接 这样高的树的最大高度一定不会改变。
    如果合并时，两棵树一样高，那么合并后，被嫁接的那棵树高度就要加1。
    */
};

// 并查集应用
/*
例1：修改数组
给定一个长度为N的数组A[]，数组中有可能有重复出现的整数。
现在按照以下方法修改为没有重复整数的数组：
依次修改A[2],A[3],···,A[N]。当修改A[i]时，检查A[i]是否在A[1]~A[i-1]出现过，
如果出现过，则给A[i]加上1；如果新的A[i]仍在之前出现过，则持续给A[i]加1直到没有出现过为止
输出最终的A[1]~A[N]

解决方案：本题的特殊情况会做大量的检查，因为要持续给A[i]加1直到它没有出现过。
即：问题出在相同的数字上，当处理一个新的A[i]时，需要检查所有与它相同的数字。
如果将这些相同的数字看成一个集，就可以用并查集进行处理。
用并查集s[i]表示访问到i这个数时应该将它换成的数字
*/
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int s[N];
int arr[N];
int find_root(int x)
{
    return s[x] = (x == s[x] ? x : find_root(s[x]));
}
int Array_arrangement_main()
{
    for (int i = 1; i < N; i++)
        s[i] = i;
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
        int root = find_root(arr[i]);  // 找到A[i]的根，即找到A[i]应该被修改成什么
        arr[i] = root;                 // 修改A[i]
        s[root] = find_root(root + 1); // 修改根为 root+1的根 这样下一次相同的数将被修改为root+1的根
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", arr[i]);
    return 0;
}
/*
例2：发现环
小明的实验室有N 台电脑，编号1-N。原本这N 台电脑之间有N−1 条数据链接相连，
恰好构成一个树形网络。在树形网络上，任意两台电脑之间有唯一的路径相连。
不过在最近一次维护网络时，管理员误操作使得某两台电脑之间增加了一条数据链接，于是网络中出现了环路。
环路上的电脑由于两两之间不再是只有一条路径，使得这些电脑上的数据传输出现了 BUG
请找到并输出所有在环路上的电脑
输入：第一行一个整数N(<1N<1e5)
      之后N行每行两个整数a,b表示a和b之间有一条数据链相连
输出：按从小到大的顺序输出环路上的电脑编号，中间由一个空格分隔
解决方法：如果直接用DFS遍历所有点，直到找到一条环路，如果路径太多就会超时。
(1)可以先读所有的边，用并查集找到环路上的一个点start
(2)之后从start出发，搜索所有路径，如果其中一条路径绕了一圈回到起点start，那么这条路径就是环路
   在DFS回溯过程中，记录环路上的点并将其输出
*/
#include <vector>
#include <algorithm>
const int N = 1e5 + 5;
vector<int> edge[N]; // 邻接表
int s[N], vis[N], ring[N];
int start, flag;
int tot;
void initialize_set()
{
    for (int i = 1; i <= N; i++)
        s[i] = i;
}
int Find_Root_Path_Compression(int x)
{
    return s[x] = (x == s[x] ? x : Find_Root_Path_Compression(s[x]));
}
void MergeSet(int x, int y)
{
    int temp = x;
    x = Find_Root_Path_Compression(x), y = Find_Root_Path_Compression(y);
    if (x != y)
        s[y] = s[x];
    else
        start = temp; // 此x和y处于环中，记录一个点。
}
void DFS(int x, int step) // 从起点start出发找到一条回start的环路
{
    if (flag)
        return;
    if (x == start) // 绕了一圈回来了，环路结束
    {
        if (vis[x] == 1)
        {
            tot = step - 1;
            flag = 1;
            return;
        }
    }
    ring[step] = x;
    for (int i = 0; i < edge[x].size(); i++)
    {
        int y = edge[x][i];
        if (!vis[y])
        {
            vis[y] = 1;
            DFS(y, step + 1);
            vis[y] = 0;
        }
    }
}
int Find_the_ring_Main()
{
    int n;
    scanf("%d", &n);
    initialize_set();
    int u, v;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
        MergeSet(u, v); // 找到换上一个点start,MergeSet()执行后，全局变量start会被赋值
    }
    flag = 0;
    DFS(start, 1); // 以start为起点再次搜索回来，这就是环
    sort(ring + 1, ring + 1 + tot);
    for (int i = 1; i <= tot; i++)
        printf("%d ", ring[i]);
    return 0;
}