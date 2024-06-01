#include "../../Heads/Head.h"
// 分块处理区间修改+区间查询问题
const int N = 1e5 + 5;
PII *Range;   // Range[i].first表示每一块的左边界 =(i-1)*BlockSize+1 Range[i].second表示每一块的右边界 =i*BlockSize
ll *Sum;      // Sum[i]表示第i个块的总和 初值需要预处理
ll *Addition; // Addition[i]表示第i块的增量,在整个块都被修改时才被修改,否则不修改,初值为0
int Pos[N];   // Pos[i]表示第i个元素所在的块
int arr[N];
void Init(int n)
{
    int BlockSize = sqrt(n);      // BlockSize为每一块的大小
    int BlockCnt = n / BlockSize; // BlockCnt为块的数量
    if (n % BlockSize)            // 如果不能正好分出k块,那么需要在末尾加一块小碎块
        BlockCnt++;
    Sum = new ll[BlockCnt + 1], Range = new PII[BlockCnt + 1], Addition = new ll[BlockCnt + 1]; // 分配内存空间
    memset(Sum, 0, sizeof(ll) * (BlockCnt + 1));                                                // 初始化
    memset(Range, 0, sizeof(PII) * (BlockCnt + 1));
    memset(Addition, 0, sizeof(ll) * (BlockCnt + 1));
    for (int i = 1; i <= BlockCnt; i++) // 遍历每一块
        Range[i].first = (i - 1) * BlockSize + 1, Range[i].second = i * BlockSize;
    Range[BlockCnt].second = n;  // sqrt(n)的结果如果不是整数,则最后一块较小 需要另外赋值Range的右端
    for (int i = 1; i <= n; i++) // 找到所有元素在块的位置
        Pos[i] = (i - 1) / BlockSize + 1;
    for (int i = 1; i <= BlockCnt; i++)
        for (int j = Range[i].first; j <= Range[i].second; j++)
            Sum[i] += arr[j];
}
/*
    区间修改:
    [1]若修改的区间[L,R]在某个块i内,即[L,R]为一个碎片,需要把arr[L]到arr[R]逐个加到Sum[i]上,
    即更新Sum[i] += (R-L+1) * Val
    [2]修改的区间[L,R]跨越了多个块,在被[L,R]完全覆盖的k个块内,更新Addition[i] += Val
    对不能被完全包含的区间碎片,按[1]处理
    即:处理碎片只更新Sum[i],处理整块只更新Addition[i]
*/
void Change(int L, int R, int Val) // 区间修改
{
    int BlockL = Pos[L], BlockR = Pos[R]; // 计算L和R所处的块
    if (BlockL == BlockR)                 // 情况1
    {
        for (int i = L; i <= R; i++)
            arr[i] += Val;
        Sum[BlockL] += (R - L + 1) * Val;
    }
    else // 情况2
    {
        for (int i = BlockL + 1; i <= BlockR - 1; i++) // 整块更新
            Addition[i] += Val;
        for (int i = L; i <= Range[BlockL].second; i++)
            arr[i] += Val;
        Sum[BlockL] += (Range[BlockL].second - L + 1) * Val;
        for (int i = Range[BlockR].first; i <= R; i++)
            arr[i] += Val;
        Sum[BlockR] += (R - Range[BlockR].first + 1) * Val;
    }
}
ll Query(int L, int R) // 区间查询
{
    int BlockL = Pos[L], BlockR = Pos[R];
    ll res = 0;
    if (BlockL == BlockR) // 情况1: 在一个块内
    {
        for (int i = L; i <= R; i++)
            res += arr[i];
        res += Addition[BlockL] * (R - L + 1);
    }
    else // 情况2: 跨越数块
    {
        for (int i = BlockL + 1; i <= BlockR - 1; i++)
            res += Sum[i] + Addition[i] * (Range[i].second - Range[i].first + 1); // 整块
        for (int i = L; i <= Range[BlockL].second; i++)
            res += arr[i];
        res += Addition[BlockL] * (Range[BlockL].second - L + 1); // 整块前面的碎片
        for (int i = Range[BlockR].first; i <= R; i++)
            res += arr[i];
        res += Addition[BlockR] * (R - Range[BlockR].first + 1); // 整块后面的碎片
    }
    return res;
}
// 修改+查询总时间复杂度O(M*sqrt(N)),其中M为查询次数,N为数据规模。 适合M*sqrt(N)=1e7的问题