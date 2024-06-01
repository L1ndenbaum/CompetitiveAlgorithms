#include "../Heads/Head.h"
// 倍增

/*
    倍增法与二分法相反,为每次扩大一倍,以O(2^n)的速度扩展为极大的区间
    主要有两种应用场合:
    [1]区间问题中,从小区间倍增到大区间,求解和区间查询有关的问题(最大、最小值)
    [2]数值的精确计算
*/

/*
    倍增法原理:
    使用二进制划分,其权值特性为:第i位的权值等于前面所有权值之和+1
    即2^i=2^(i-1)+2^(i-2)+···+2^1+2^0
    一个整数n的二进制只有logn位，从0增长到n,可以以1,2,4,···,2^n的方式增长,快速到n
    倍增法的局限性是要提前计算1,2,4,···,2^n个跳板,数据不能发生变化,否则需要重新计算。
*/

/*
    场景:
    m个哨站围成一圈,顺时针编号1-m,有n名战士,每人常驻两个哨站,能在两个哨站之间移动。
    局长有一个国旗计划,让展示举着国旗环绕一圈,他想知道至少要多少名战士才能完成国旗计划,
    并且想知道在某个战士必须参加的情况下,至少需要多少名战士。
    输出一行,包含n个正整数,第i个正整数表示战士i必须参加的情况下需要多少名战士才能顺利完成国旗计划。
    (n<=2e5, m<1e9, 所有区间不互相包含)

    基本思路是贪心,如果所有区间按左端点排序后,区间右端点也是单调递增的
    先化圆为线,断开圆,成为一个线,为了保证首尾相接,需要额外复制一条线接到断开的圆形成的线上
    选择一个区间i后,找下一个左端点 <= i的右端点的区间,且保证这个区间右端点最大,它就是最优的区间
    轮流选择,直到覆盖整个圆。
    本题使用倍增算法,可以先算出一些跳板,快速找到后面的区间
    定义Go[s][i]表示从第s个区间出发,走2^i个最优区间后到达的区间。
    如:Go[s][4]是从s出发到达的2^4=16个最优的区间,s和Go[s][4]之间的区间也都是最优的。
    预计算出所有的区间出发的Go[][],以它们为跳板,就能快速走完整个圆。
    一次查询logn,所有查询一共O(nlogn)复杂度

    注意:跳的时候要先用大数再用小数,如16+8+2+1=27步(27的二进制是11011),因为一个数转换为二进制数时,
        时从最高位向最低位转换的。

    Go[][]数组的计算,有递推关系:
    Go[s][i]=Go[Go[s][i-1]][i-1]
    (1)Go[s][i]为从s起跳,先跳2^(i-1)步到区间z=Go[s][i-1]
    (2)从z跳2^(i-1)步,到达区间Go[z][i-1],一共跳了2^i步,即从s起跳,跳2^i步,到达了Go[s][i]
    特别地,Go[s][0]是s后第1个区间(即用贪心法算出的下一个最优区间),是递推式的初始条件,由它推出了所有的Go[][]。
*/
const int N = 4e5 + 10;
int n, m;
struct soldiers
{
    int id, L, R;
    bool operator<(soldiers s)
    {
        return L < s.L;
    }
} soldier[N * 2];
int n2, Go[N][20], res[N];
void Init() // 用贪心法预处理倍增
{
    int next = 1;
    for (int i = 1; i <= n2; i++)
    {
        while (next <= n2 && soldier[next].L <= soldier[i].R) // 找到最优区间
            next++;
        Go[i][0] = next - 1;
    }
    for (int i = 1; (1 << i) <= n; i++)
        for (int s = 1; s <= n2; s++)
            Go[s][i] = Go[Go[s][i - 1]][i - 1];
}
void GetAns(int x) // 从第x个战士出发
{
    int Len = soldier[x].L + m, current = x, ans = 1;
    for (int i = log2(N); i >= 0; i--)
    {
        int pos = Go[current][i];
        if (pos && soldier[pos].R < Len)
        {
            ans += 1 << i;
            current = pos;
        }
    }
    res[soldier[x].id] = ans + 1;
}
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        soldier[i].id = i; // 记录战士顺序
        scanf("%d %d", &soldier[i].L, &soldier[i].R);
        if (soldier[i].R < soldier[i].L)
            soldier[i].R += m; // 环变成链
    }
    sort(soldier + 1, soldier + 1 + n);
    n2 = n;
    for (int i = 1; i <= n; i++) // 拆环加倍成一条链
    {
        n2++;
        soldier[n2] = soldier[i];
        soldier[n2].L = soldier[i].L + m;
        soldier[n2].R = soldier[i].R + m;
    }
    Init();
    for (int i = 1; i <= n; i++)
        GetAns(i);
    for (int i = 1; i <= n; i++)
        printf("%d", res[i]);
}