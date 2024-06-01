#include "../../Heads/Head.h"
// 莫队算法 = 离线 + 暴力 + 分块

/*
    例: 给定一个长度为n的数列,查询m次,每次询问数列某个区间内不同的数有多少个
    本题的莫队算法是对暴力法的优化

    暴力法:
    如果只考虑一次查询的情况,用两个指针L,R从头扫到查询区间,
    L每扫过一个数,cnt[arr[x]]--,R每扫过一个数,cnt[arr[x]]++
    当cnt[arr[x]]=1时,说明这个数只出现了一次,ans++
    当cnt[arr[x]]=0时,说明这个数在一前一后两次扫描中被抵消了,它并不在区间内,ans--
    考虑n次的情况,先对每次查询的L排序,循环移动L,R到所需位置,如果L或R发生与本应移动的方向相反的移动,那么cnt[arr[x]]的增减也相反
    这样每次变换区间时,L,R会发生较大的变动,需要的时间更多。

    莫队算法是先分块,当每个L所在的块不同时,按L所在块排序,否则按R排序
    这样降低了L,R指针的震荡距离,从而减少了复杂度

    不带修改的莫队算法时间复杂度O(N*sqrt(N))
*/
const int N = 1e6 + 5;
struct Node // 离线记录查询操作
{
    int L, R, k; // L,R为每次查询的区间,k为查询操作的原始顺序
} Q[N];
int Pos[N], ans[N], cnt[N], arr[N], ANS;
bool Compare(Node &n1, Node &n2)
{
    if (Pos[n1.L] != Pos[n2.L]) // 如果两个查询区间的L不在同一个块内,就按照L所在的块位置排序
        return Pos[n1.L] < Pos[n2.L];
    if (Pos[n1.L] & 1) // 奇偶性优化 对编号为奇数的块,R大的排在前面
        return n1.R > n2.R;
    return n1.R < n2.R; // 否则按照R的位置(而不是按照R所在的块位置)排序
}
void Add(int x) // 扩大区间时(L左移或者R右移),增加数arr[x]的出现次数
{
    cnt[arr[x]]++;
    if (cnt[arr[x]] == 1) // 这个数第一次出现  ANS加1
        ANS++;
}
void Del(int x) // 缩小区间时(L右移或者R左移),减少数arr[x]的出现次数
{
    cnt[arr[x]]--;
    if (cnt[arr[x]] == 0) // 这个数消失了 ANS减1
        ANS--;
}
int main()
{
    int n;
    scanf("%d", &n);
    int BlockSize = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
        Pos[i] = (i - 1) / BlockSize + 1;
    }
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) // 离线记录每次查询的区间
    {
        scanf("%d %d", &Q[i].L, &Q[i].R);
        Q[i].k = i;
    }
    sort(Q + 1, Q + 1 + m, Compare); // 对查询的顺序排序
    int L = 1, R = 0;                // 左右指针初始化 R应被初始化为0 这样才能扫描到前面的所有数
    for (int i = 1; i <= m; i++)
    {
        while (L < Q[i].L)
            Del(L++);
        while (R > Q[i].R)
            Del(R--);
        while (L > Q[i].L)
            Add(--L);
        while (R < Q[i].R)
            Add(++R);
        ans[Q[i].k] = ANS;
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
}