#include "../Heads/Head.h"
/*
    ST算法基于倍增原理,适用于求解静态的区间最值查询
    ST算法原理:
    一个大区间如果能被两个小区间覆盖,那么大区间的最值等于两个小区间的最值.

    ST算法的步骤:
    [1]将数列分为多个小区间,提前计算每个小区间的最值
        用2的幂次的长度划分数组,第一组每块长度为1,第二组每块长度为2,长度>=2的每组中的小块的尾部和它下一块的头部重叠
        每组的小区间最值可以从前一组推出: dp[s][k]表示区间左端点为s,长度为2^k的区间的最值,以最小值为例,转移方程为:
        dp[s][k]=min(dp[s][k-1],dp[s + (1<<(k-1))][k-1]),其中1<<(k-1) 表示2^(k-1)
        时间复杂度O(NlogN)
    [2]对任意区间最值查询,找到覆盖它的两个小区间,由两个小区间的最值算出答案
        有以下结论:
        (1)以任意元素为起点,有长度为1,2,4,等的小区间;以任意元素为终点,它前面也有长度为1,2,4,等的小区间
        (2)有以任意元素为起点的小区间,也有以任意元素为终点的小区间
        由上可以将查询的区间[L,R]分为两个小区间,它们属于同一组:以L为起点的小区间和以R为终点的小区间
        让他们首尾相接覆盖[L,R],区间最值由两个小区间的最值求得,时间复杂度O(1)
        区间[L,R]长Len=R-L+1,两个小区间的长度都为x,令x为比Len小的2的最大倍数,x<=Len且2*x>=Len,即可保证能覆盖整个区间
        有2^k=x,求k可用 k = log2(Len) = log10(Len) / log10(2)向下取整 (即(int)(log(double(R-L+1))/log(2.0)))
        库函数log2()比较慢,可以提前自己算出LOG2[i],其与向下取整的log2(i)相等
        LOG2[0]=-1;
        for(int i=1;i<=N;i++)
            LOG2[i]=LOG2[i>>1]+1;
        最后,区间[L,R]最小值为min(dp[L][k],dp[R-(1<<k)+1][k])
*/

// 查询区间[L,R]最大值与最小值的差值
const int N = 5e4 + 5;
int n, m; // n个数 m次查询
int arr[N], dp_max[N][25], dp_min[N][25];
int LOG2[N];
void InitST() // ST初始化
{
    LOG2[0] = -1;
    for (int i = 1; i <= N; i++)
        LOG2[i] = LOG2[i >> 1] + 1;
    for (int i = 1; i <= n; i++) // 初始化ST区间长度为1时候的初始值
        dp_max[i][0] = arr[i], dp_min[i][0] = arr[i];
    int p = LOG2[n];             // 可倍增区间的最大次方: 2^p <= n
    for (int k = 1; k <= p; k++) // 倍增计算小区间,先算小区间,后算大区间,逐步递推
    {
        for (int s = 1; s + (1 << k) <= n + 1; s++)
        {
            dp_min[s][k] = min(dp_min[s][k - 1], dp_min[s + (1 << (k - 1))][k - 1]);
            dp_max[s][k] = max(dp_max[s][k - 1], dp_max[s + (1 << (k - 1))][k - 1]);
        }
    }
}
int ST_Query(int L, int R)
{
    int k = LOG2[R - L + 1];
    int maxV = max(dp_max[L][k], dp_max[R - (1 << k) + 1][k]);
    int minV = min(dp_min[L][k], dp_min[R - (1 << k) + 1][k]);
    return maxV - minV;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    InitST();
    while (m--)
    {
        int L, R;
        cin >> L >> R;
        cout << ST_Query(L, R) << endl;
    }
}